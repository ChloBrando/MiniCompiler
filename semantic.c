/* Simple semantic/type checker for the Mini language
 * - Tracks declarations through symtab (uses addVar/addStringVar/addArrayVar)
 * - Computes expression types (int or string)
 * - Errors on mismatched operations (e.g., int + string)
 */

#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"
#include "symtab.h"

/* Forward: compute type of expression; returns TYPE_INT, TYPE_STRING, or -1 on error */
int exprType(ASTNode* node) {
    if (!node) return -1;
    switch (node->type) {
        case NODE_NUM:
            return TYPE_INT;
        case NODE_STR:
            return TYPE_STRING;
        case NODE_VAR: {
            int off = getVarOffset(node->data.name);
            if (off == -1) {
                fprintf(stderr, "Semantic Error: variable '%s' not declared\n", node->data.name);
                return -1;
            }
            if (isStringVar(node->data.name)) return TYPE_STRING;
            if (isArrayVar(node->data.name)) return TYPE_ARRAY_INT;
            return TYPE_INT;
        }
        case NODE_ARRAY_ACCESS: {
            if (!isArrayVar(node->data.arrayAccess.name)) {
                fprintf(stderr, "Semantic Error: %s is not an array\n", node->data.arrayAccess.name);
                return -1;
            }
            int t = exprType(node->data.arrayAccess.index);
            if (t != TYPE_INT) {
                fprintf(stderr, "Semantic Error: array index must be integer\n");
                return -1;
            }
            return TYPE_INT;
        }
        case NODE_BINOP: {
            int lt = exprType(node->data.binop.left);
            int rt = exprType(node->data.binop.right);
            if (lt == -1 || rt == -1) return -1;
            if (node->data.binop.op == '+') {
                /* allow int+int -> int, string+string -> string */
                if (lt == TYPE_INT && rt == TYPE_INT) return TYPE_INT;
                if ((lt == TYPE_STRING || lt == TYPE_ARRAY_INT) && (rt == TYPE_STRING || rt == TYPE_ARRAY_INT)) return TYPE_STRING;
                fprintf(stderr, "Semantic Error: incompatible types for '+' (left=%d right=%d)\n", lt, rt);
                return -1;
            } else if (node->data.binop.op == '-') {
                if (lt == TYPE_INT && rt == TYPE_INT) return TYPE_INT;
                fprintf(stderr, "Semantic Error: '-' requires integer operands\n");
                return -1;
            }
            return -1;
        }
        case NODE_FUNC_CALL: {
            /* Function calls always return int for now */
            /* In a full implementation, you'd look up the function's return type */
            return TYPE_INT;
        }
        default:
            return -1;
    }
}

/* Walk statements to check declarations, assignments, and prints */
int checkStmt(ASTNode* node) {
    if (!node) return 0;
    switch (node->type) {
        case NODE_DECL: {
            int off = addVar(node->data.name);
            if (off == -1) {
                fprintf(stderr, "Semantic Error: variable '%s' already declared\n", node->data.name);
                return -1;
            }
            return 0;
        }
        case NODE_STR_DECL: {
            int off = addStringVar(node->data.name);
            if (off == -1) {
                fprintf(stderr, "Semantic Error: variable '%s' already declared\n", node->data.name);
                return -1;
            }
            return 0;
        }
        case NODE_ARRAY_DECL: {
            int off = addArrayVar(node->data.arrayDecl.name, node->data.arrayDecl.size);
            if (off == -1) {
                fprintf(stderr, "Semantic Error: array '%s' already declared\n", node->data.arrayDecl.name);
                return -1;
            }
            return 0;
        }
        case NODE_ASSIGN: {
            int off = getVarOffset(node->data.assign.var);
            if (off == -1) {
                fprintf(stderr, "Semantic Error: variable '%s' not declared\n", node->data.assign.var);
                return -1;
            }
            int ltype = isStringVar(node->data.assign.var) ? TYPE_STRING : (isArrayVar(node->data.assign.var) ? TYPE_ARRAY_INT : TYPE_INT);
            int rtype = exprType(node->data.assign.value);
            if (rtype == -1) return -1;
            if (ltype == TYPE_INT && rtype != TYPE_INT) {
                fprintf(stderr, "Semantic Error: cannot assign non-int to int variable '%s'\n", node->data.assign.var);
                return -1;
            }
            if (ltype == TYPE_STRING && rtype != TYPE_STRING) {
                fprintf(stderr, "Semantic Error: cannot assign non-string to string variable '%s'\n", node->data.assign.var);
                return -1;
            }
            if (ltype == TYPE_ARRAY_INT) {
                fprintf(stderr, "Semantic Error: cannot assign to an array name directly '%s'\n", node->data.assign.var);
                return -1;
            }
            return 0;
        }
        case NODE_PRINT: {
            int t = exprType(node->data.expr);
            if (t == -1) return -1;
            return 0;
        }
        case NODE_STMT_LIST:
            if (checkStmt(node->data.stmtlist.stmt) != 0) return -1;
            if (checkStmt(node->data.stmtlist.next) != 0) return -1;
            return 0;
        case NODE_ARRAY_ASSIGN: {
            if (!isArrayVar(node->data.arrayAssign.name)) {
                fprintf(stderr, "Semantic Error: %s is not an array\n", node->data.arrayAssign.name);
                return -1;
            }
            int idxType = exprType(node->data.arrayAssign.index);
            if (idxType != TYPE_INT) {
                fprintf(stderr, "Semantic Error: array index must be integer\n");
                return -1;
            }
            int valType = exprType(node->data.arrayAssign.value);
            if (valType != TYPE_INT) {
                fprintf(stderr, "Semantic Error: array value must be integer\n");
                return -1;
            }
            return 0;
        }
        case NODE_FUNC_DECL: {
            /* Add function to symbol table */
            int result = addFunction(node->data.funcDecl.name, "int", NULL, 0);
            if (result == -1) {
                fprintf(stderr, "Semantic Error: function '%s' already declared\n", node->data.funcDecl.name);
                return -1;
            }

            /* Enter new scope for function body */
            enterScope();

            /* Add parameters to the new scope */
            ASTNode* param = node->data.funcDecl.params;
            while (param) {
                int paramOffset = addParameter(param->data.param.name, "int");
                if (paramOffset == -1) {
                    fprintf(stderr, "Semantic Error: duplicate parameter '%s'\n", param->data.param.name);
                    exitScope();
                    return -1;
                }
                param = param->data.param.next;
            }

            /* Check function body */
            int bodyResult = checkStmt(node->data.funcDecl.body);

            /* Exit function scope */
            exitScope();

            return bodyResult;
        }
        case NODE_RETURN: {
            /* Check return expression type */
            if (node->data.expr) {
                int t = exprType(node->data.expr);
                if (t == -1) return -1;
            }
            return 0;
        }
        case NODE_PARAM: {
            /* Parameters are handled in NODE_FUNC_DECL */
            return 0;
        }
        default:
            return 0;
    }
}

int semanticCheck(ASTNode* root) {
    if (!root) return 0;
    return checkStmt(root);
}
