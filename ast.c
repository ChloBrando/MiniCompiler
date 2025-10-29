/* AST IMPLEMENTATION
 * Functions to create and manipulate Abstract Syntax Tree nodes
 * The AST is built during parsing and used for all subsequent phases
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "ast.h"

/* ===========================================================
 * Helpers for constant folding / simplification
 * ===========================================================
 */
static int isConst(ASTNode* n) {
    return n && n->type == NODE_NUM;
}
static int getConst(ASTNode* n) {
    return n->data.num;
}


/* Algebraic simplifications when at least one side is constant.
   Returns either the original node (possibly modified) or a child
   that should replace this node. */
static ASTNode* simplifyBinopIfAlgebraic(ASTNode* node) {
    if (!node || node->type != NODE_BINOP) return node;
    ASTNode* L = node->data.binop.left;
    ASTNode* R = node->data.binop.right;
    char op = node->data.binop.op;

    /* x + 0 or 0 + x */
    if (op == '+') {
        if (isConst(R) && getConst(R) == 0) return L ? L : node;
        if (isConst(L) && getConst(L) == 0) return R ? R : node;
    }

    /* x - 0 */
    if (op == '-') {
        if (isConst(R) && getConst(R) == 0) return L ? L : node;
        /* Note: we do NOT rewrite 0 - x (no unary node in this AST). */
    }

    /* x * 1, 1 * x, x * 0, 0 * x */
    if (op == '*') {
        if (isConst(R) && getConst(R) == 1) return L ? L : node;
        if (isConst(L) && getConst(L) == 1) return R ? R : node;
        if ((isConst(R) && getConst(R) == 0) || (isConst(L) && getConst(L) == 0)) {
            node->type = NODE_NUM;
            node->data.num = 0;
            node->data.binop.left = node->data.binop.right = NULL; /* detach */
            return node;
        }
    }

    /* x / 1 */
    if (op == '/') {
        if (isConst(R) && getConst(R) == 1) return L ? L : node;
        /* Avoid 0/x -> 0 rewrite to stay conservative around division by 0. */
    }

    return node;
}

/* Post-order constant folding. Rewrites subtrees in place and may
   return a different node pointer to be spliced into the parent. */
ASTNode* foldConstants(ASTNode* node) {
    if (!node) return NULL;

    switch (node->type) {
        case NODE_NUM:
        case NODE_FLOAT:
        case NODE_STR:
        case NODE_VAR:
        case NODE_DECL:
        case NODE_STR_DECL:
        case NODE_FLOAT_DECL:
            return node;

        case NODE_BINOP: {
            node->data.binop.left  = foldConstants(node->data.binop.left);
            node->data.binop.right = foldConstants(node->data.binop.right);

            ASTNode* L = node->data.binop.left;
            ASTNode* R = node->data.binop.right;
            char op = node->data.binop.op;

            /* If both sides are constants, fully evaluate. */
            if (isConst(L) && isConst(R)) {
                int a = getConst(L), b = getConst(R);
                int ok = 1;
                long long res = 0;
                switch (op) {
                    case '+': res = (long long)a + (long long)b; break;
                    case '-': res = (long long)a - (long long)b; break;
                    case '*': res = (long long)a * (long long)b; break;
                    case '/':
                        if (b == 0) ok = 0; else res = a / b;
                        break;
                    default:
                        ok = 0;
                }
                if (ok) {
                    node->type = NODE_NUM;
                    node->data.num = (int)res;
                    node->data.binop.left = node->data.binop.right = NULL; /* detach */
                    return node;
                }
            }

            /* Otherwise try simple algebraic simplifications. */
            ASTNode* simplified = simplifyBinopIfAlgebraic(node);
            return simplified;
        }

        case NODE_COMPARE: {
            /* Fold constants in comparison operands */
            node->data.compare.left = foldConstants(node->data.compare.left);
            node->data.compare.right = foldConstants(node->data.compare.right);
            return node;
        }

        case NODE_ASSIGN:
            node->data.assign.value = foldConstants(node->data.assign.value);
            return node;

        case NODE_PRINT:
            node->data.expr = foldConstants(node->data.expr);
            return node;

        case NODE_STMT_LIST:
            node->data.stmtlist.stmt = foldConstants(node->data.stmtlist.stmt);
            node->data.stmtlist.next = foldConstants(node->data.stmtlist.next);
            return node;

        case NODE_ARRAY_DECL:
            /* size is an int already; nothing to fold */
            return node;

        case NODE_FLOAT_ARRAY_DECL:
            /* size is an int already; nothing to fold */
            return node;

        case NODE_ARRAY_ASSIGN:
            node->data.arrayAssign.index = foldConstants(node->data.arrayAssign.index);
            node->data.arrayAssign.value = foldConstants(node->data.arrayAssign.value);
            return node;

        case NODE_ARRAY_ACCESS:
            node->data.arrayAccess.index = foldConstants(node->data.arrayAccess.index);
            return node;

        case NODE_IF:
            node->data.ifStmt.condition = foldConstants(node->data.ifStmt.condition);
            node->data.ifStmt.thenStmt = foldConstants(node->data.ifStmt.thenStmt);
            if (node->data.ifStmt.elseStmt) {
                node->data.ifStmt.elseStmt = foldConstants(node->data.ifStmt.elseStmt);
            }
            return node;

        case NODE_FUNC_DECL:
            node->data.funcDecl.body = foldConstants(node->data.funcDecl.body);
            return node;

        case NODE_PARAM:
            /* Parameters don't need constant folding */
            return node;

        case NODE_FUNC_CALL:
            if (node->data.funcCall.args) {
                node->data.funcCall.args = foldConstants(node->data.funcCall.args);
            }
            return node;

        case NODE_RETURN:
            if (node->data.returnStmt.value) {
                node->data.returnStmt.value = foldConstants(node->data.returnStmt.value);
            }
            return node;
    }
    return node; /* defensive */
}

/* ===========================================================
 * Constructors
 * ===========================================================
 */

/* Create a number literal node */
ASTNode* createNum(int value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_NUM;
    node->data.num = value;  /* Store the integer value */
    return node;
}

/* Create a variable reference node */
ASTNode* createVar(char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_VAR;
    node->data.name = strdup(name);  /* Copy the variable name */
    return node;
}

/* Create a binary operation node (supports '+', '-', '*', '/') */
ASTNode* createBinOp(char op, ASTNode* left, ASTNode* right) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_BINOP;
    node->data.binop.op = op;        /* Operator */
    node->data.binop.left = left;    /* Left subtree */
    node->data.binop.right = right;  /* Right subtree */
    return node;
}

/* Create a comparison operation node (supports ==, !=, <, >, <=, >=) */
ASTNode* createCompareOp(int op, ASTNode* left, ASTNode* right) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_COMPARE;
    node->data.compare.compOp = op;   /* Comparison operator */
    node->data.compare.left = left;   /* Left subtree */
    node->data.compare.right = right; /* Right subtree */
    return node;
}

/* Create a string literal node */
ASTNode* createStr(char* s) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_STR;
    node->data.str = strdup(s);
    return node;
}

/* Create a variable declaration node */
ASTNode* createDecl(char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_DECL;
    node->data.name = strdup(name);  /* Store variable name */
    return node;
}

/* Create a string declaration node */
ASTNode* createStrDecl(char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_STR_DECL;
    node->data.name = strdup(name);
    return node;
}

/* Create an assignment statement node */
ASTNode* createAssign(char* var, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ASSIGN;
    node->data.assign.var = strdup(var);  /* Variable name */
    node->data.assign.value = value;      /* Expression tree */
    return node;
}

/* Create a print statement node */
ASTNode* createPrint(ASTNode* expr) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_PRINT;
    node->data.expr = expr;  /* Expression to print */
    return node;
}

/* Create a statement list node (links statements together) */
ASTNode* createStmtList(ASTNode* stmt1, ASTNode* stmt2) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_STMT_LIST;
    node->data.stmtlist.stmt = stmt1;  /* First statement */
    node->data.stmtlist.next = stmt2;  /* Rest of list */
    return node;
}

/* Create an array declaration node */
ASTNode* createArrayDecl(char* name, int size) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY_DECL;
    node->data.arrayDecl.name = strdup(name);  /* Array name */
    node->data.arrayDecl.size = size;          /* Array size */
    return node;
}

/* Create an array element assignment node */
ASTNode* createArrayAssign(char* name, ASTNode* index, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY_ASSIGN;
    node->data.arrayAssign.name = strdup(name); /* Array name */
    node->data.arrayAssign.index = index;       /* Index expression */
    node->data.arrayAssign.value = value;       /* Value expression */
    return node;
}

/* Create an array element access node */
ASTNode* createArrayAccess(char* name, ASTNode* index) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_ARRAY_ACCESS;
    node->data.arrayAccess.name = strdup(name); /* Array name */
    node->data.arrayAccess.index = index;       /* Index expression */
    return node;
}

/* Create a floating-point number node */
ASTNode* createFloatNum(float value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FLOAT;
    node->data.fnum = value;  /* Store the floating-point value */
    return node;
}

/* Create a float declaration node */
ASTNode* createFloatDecl(char* name) {
    printf("DEBUG: createFloatDecl called for '%s'\n", name);
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FLOAT_DECL;
    node->data.name = strdup(name);
    printf("DEBUG: createFloatDecl created node with type %d (NODE_FLOAT_DECL=%d)\n", 
           node->type, NODE_FLOAT_DECL);
    return node;
}
/* Create a float array declaration node */
ASTNode* createFloatArrayDecl(char* name, int size) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FLOAT_ARRAY_DECL;
    node->data.arrayDecl.name = strdup(name);  /* Array name */
    node->data.arrayDecl.size = size;          /* Array size */
    return node;
}

/* Create an if statement node */
ASTNode* createIfNode(ASTNode* condition, ASTNode* thenStmt, ASTNode* elseStmt) {
    ASTNode* node = malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Error: Memory allocation failed for if node\n");
        exit(1);
    }
    
    node->type = NODE_IF;
    node->data.ifStmt.condition = condition;
    node->data.ifStmt.thenStmt = thenStmt;
    node->data.ifStmt.elseStmt = elseStmt;  /* Can be NULL for simple if */
    
    return node;
}

/* Create a string literal node (for STRING_LITERAL token) */
ASTNode* createStringLit(char* s) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_STR;
    node->data.str = strdup(s);
    return node;
}

/* Create a function declaration node */
ASTNode* createFuncDecl(char* name, ASTNode* params, ASTNode* body) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FUNC_DECL;
    node->data.funcDecl.name = strdup(name);
    node->data.funcDecl.params = params;
    node->data.funcDecl.body = body;
    return node;
}

/* Create a parameter node */
ASTNode* createParam(char* name, char* type) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_PARAM;
    node->data.param.name = strdup(name);
    node->data.param.type = strdup(type);
    node->data.param.next = NULL;
    return node;
}

/* Add parameter to existing parameter list */
ASTNode* addParam(ASTNode* list, char* name, char* type) {
    ASTNode* newParam = createParam(name, type);
    if (!list) {
        return newParam;
    }
    
    // Find the end of the parameter list
    ASTNode* current = list;
    while (current->data.param.next) {
        current = current->data.param.next;
    }
    current->data.param.next = newParam;
    return list;
}

/* Create a function call node */
ASTNode* createFuncCall(char* name, ASTNode* args) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_FUNC_CALL;
    node->data.funcCall.name = strdup(name);
    node->data.funcCall.args = args;
    return node;
}

/* Create a return statement node */
ASTNode* createReturn(ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_RETURN;
    node->data.returnStmt.value = value;
    return node;
}

/* ===========================================================
 * Pretty-printer
 * ===========================================================
 */

void printAST(ASTNode* node, int level) {
    if (!node) return;

    /* Indent based on tree depth */
    for (int i = 0; i < level; i++) printf("  ");

    /* Print node based on its type */
    switch (node->type) {
        case NODE_NUM:
            printf("NUM: %d\n", node->data.num);
            break;

        case NODE_STR:
            printf("STR: %s\n", node->data.str);
            break;

        case NODE_VAR:
            printf("VAR: %s\n", node->data.name);
            break;

        case NODE_BINOP:
            printf("BINOP: %c\n", node->data.binop.op);
            printAST(node->data.binop.left, level + 1);
            printAST(node->data.binop.right, level + 1);
            break;

        case NODE_COMPARE:
            printf("COMPARE: ");
            switch(node->data.compare.compOp) {
                case '<': printf("<\n"); break;
                case '>': printf(">\n"); break;
                case 271: printf("==\n"); break;  /* EQ token */
                case 272: printf("!=\n"); break;  /* NE token */
                case 273: printf("<=\n"); break;  /* LE token */
                case 274: printf(">=\n"); break;  /* GE token */
                default: printf("CMP(%d)\n", node->data.compare.compOp); break;
            }
            printAST(node->data.compare.left, level + 1);
            printAST(node->data.compare.right, level + 1);
            break;

        case NODE_DECL:
            printf("DECL: %s\n", node->data.name);
            break;

        case NODE_FLOAT:
            printf("FLOAT: %f\n", node->data.fnum);
            break;

        case NODE_STR_DECL:
            printf("STR_DECL: %s\n", node->data.name);
            break;

        case NODE_FLOAT_DECL:
            printf("FLOAT_DECL: %s\n", node->data.name);
            break;

        case NODE_ASSIGN:
            printf("ASSIGN: %s\n", node->data.assign.var);
            printAST(node->data.assign.value, level + 1);
            break;

        case NODE_PRINT:
            printf("PRINT\n");
            printAST(node->data.expr, level + 1);
            break;

        case NODE_STMT_LIST:
            /* Print statements in sequence at same level */
            printAST(node->data.stmtlist.stmt, level);
            printAST(node->data.stmtlist.next, level);
            break;

        case NODE_ARRAY_DECL:
            printf("%*sARRAY_DECL: %s[%d]\n",
                   level * 2, "", node->data.arrayDecl.name, node->data.arrayDecl.size);
            break;

        case NODE_FLOAT_ARRAY_DECL:
            printf("%*sFLOAT_ARRAY_DECL: %s[%d]\n",
                   level * 2, "", node->data.arrayDecl.name, node->data.arrayDecl.size);
            break;

        case NODE_ARRAY_ASSIGN:
            printf("%*sARRAY_ASSIGN: %s[] =\n", level * 2, "", node->data.arrayAssign.name);
            printf("%*sIndex:\n", level * 2, "");
            printAST(node->data.arrayAssign.index, level + 1);
            printf("%*sValue:\n", level * 2, "");
            printAST(node->data.arrayAssign.value, level + 1);
            break;

        case NODE_ARRAY_ACCESS:
            printf("%*sARRAY_ACCESS: %s[]\n", level * 2, "", node->data.arrayAccess.name);
            printf("%*sIndex:\n", level * 2, "");
            printAST(node->data.arrayAccess.index, level + 1);
            break;

        case NODE_FUNC_DECL:
            printf("FUNC_DECL: %s\n", node->data.funcDecl.name);
            if (node->data.funcDecl.params) {
                printf("%*sParameters:\n", (level+1)*2, "");
                printAST(node->data.funcDecl.params, level+2);
            }
            printf("%*sBody:\n", (level+1)*2, "");
            printAST(node->data.funcDecl.body, level+2);
            break;

        case NODE_PARAM:
            printf("PARAM: %s %s\n", node->data.param.type, node->data.param.name);
            if (node->data.param.next) {
                printAST(node->data.param.next, level);
            }
            break;

        case NODE_FUNC_CALL:
            printf("FUNC_CALL: %s\n", node->data.funcCall.name);
            if (node->data.funcCall.args) {
                printf("%*sArguments:\n", (level+1)*2, "");
                printAST(node->data.funcCall.args, level+2);
            }
            break;

        case NODE_RETURN:
            printf("RETURN\n");
            if (node->data.returnStmt.value) {
                printAST(node->data.returnStmt.value, level+1);
            }
            break;

        case NODE_IF:
            printf("IF\n");
            printf("%*sCondition:\n", level * 2, "");
            printAST(node->data.ifStmt.condition, level + 1);
            printf("%*sThen:\n", level * 2, "");
            printAST(node->data.ifStmt.thenStmt, level + 1);
            if (node->data.ifStmt.elseStmt) {
                printf("%*sElse:\n", level * 2, "");
                printAST(node->data.ifStmt.elseStmt, level + 1);
            }
            break;
    }
}