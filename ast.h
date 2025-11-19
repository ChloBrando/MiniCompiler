#ifndef AST_H
#define AST_H

/* ABSTRACT SYNTAX TREE (AST)
 * The AST is an intermediate representation of the program structure
 * It represents the hierarchical syntax of the source code
 * Each node represents a construct in the language
 */

/* NODE TYPES - Different kinds of AST nodes in our language */
typedef enum {
    NODE_NUM,       /* Numeric literal (e.g., 42) */
    NODE_FLOAT,     /* Float literal (e.g., 3.14) */
    NODE_STR,       /* String literal (e.g., "hello") */
    NODE_STR_DECL,  /* String variable declaration (e.g., string s;) */
    NODE_FLOAT_DECL, /* Float variable declaration (e.g., float x;) */
    NODE_VAR,       /* Variable reference (e.g., x) */
    NODE_BINOP,     /* Binary operation (e.g., x + y) */
    NODE_COMPARE,   /* Comparison operation (e.g., x == y, x < y) */
    NODE_DECL,      /* Variable declaration (e.g., int x) */
    NODE_ASSIGN,    /* Assignment statement (e.g., x = 10) */
    NODE_PRINT,     /* Print statement (e.g., print(x)) */
    NODE_STMT_LIST,  /* List of statements (program structure) */
    NODE_ARRAY_DECL, /* Array declaration (e.g., int x[10]) */
    NODE_FLOAT_ARRAY_DECL, /* Float array declaration (e.g., float x[10]) */
    NODE_ARRAY_ASSIGN, /* Array element assignment (e.g., arr[2] = 5) */
    NODE_ARRAY_ACCESS, /* Array element access (e.g., arr[2]) */
    NODE_FUNC_DECL,   /* Function declaration (e.g., # add(int x) { ... }) */
    NODE_PARAM,       /* Function parameter */
    NODE_FUNC_CALL,   /* Function call (e.g., add(5, 3)) */
    NODE_RETURN,      /* Return statement */
    NODE_IF,          /* If statement (e.g., if (x > 0) { ... } else { ... }) */
    NODE_INPUT        /* Input statement (e.g., input()) */
} NodeType;

/* AST NODE STRUCTURE
 * Uses a union to efficiently store different node data
 * Only the relevant fields for each node type are used
 */
typedef struct ASTNode {
    NodeType type;  /* Identifies what kind of node this is */
    
    /* Union allows same memory to store different data types */
    union {
        /* Literal number value (NODE_NUM) */
        int num;

        /* Literal float value (NODE_FLOAT) */
        float fnum;

        /* String literal value (NODE_STR) */
        char* str;
        
        /* Variable or declaration name (NODE_VAR, NODE_DECL) */
        char* name;
        
        /* Binary operation structure (NODE_BINOP) */
        struct {
            char op;                    /* Operator character ('+', '-', etc.) */
            struct ASTNode* left;       /* Left operand */
            struct ASTNode* right;      /* Right operand */
        } binop;

        /* Comparison operation structure (NODE_COMPARE) */
        struct {
            int compOp;                 /* Comparison operator (EQ, NE, LT, GT, LE, GE) */
            struct ASTNode* left;       /* Left operand */
            struct ASTNode* right;      /* Right operand */
        } compare;
        
        /* Assignment structure (NODE_ASSIGN) */
        struct {
            char* var;                  /* Variable being assigned to */
            struct ASTNode* value;      /* Expression being assigned */
        } assign;
        
        /* Print expression (NODE_PRINT) */
        struct ASTNode* expr;
        
        /* Statement list structure (NODE_STMT_LIST) */
        struct {
            struct ASTNode* stmt;       /* Current statement */
            struct ASTNode* next;       /* Rest of the list */
        } stmtlist;

        /* Array declaration structure (NODE_ARRAY_DECL) */
        struct {
            char* name;                 /* Array name */
            int size;                   /* Size of the array */
        } arrayDecl;    

        /* Array element assignment structure (NODE_ARRAY_ASSIGN) */
        struct {
            char* name;                 /* Array name */
            struct ASTNode* index;      /* Index expression */
            struct ASTNode* value;      /* Value expression */
        } arrayAssign;

        /* Array element access structure (NODE_ARRAY_ACCESS) */
        struct {
            char* name;                 /* Array name */
            struct ASTNode* index;      /* Index expression */
        } arrayAccess;

        /* Function declaration structure (NODE_FUNC_DECL) */
        struct {
            char* name;                     /* Function name */
            struct ASTNode* params;         /* Parameter list */
            struct ASTNode* body;           /* Function body (stmt_list) */
        } funcDecl;

        /* Parameter structure (NODE_PARAM) */
        struct {
            char* name;                     /* Parameter name */
            char* type;                     /* Parameter type: "int" or "float" */
            int isArray;                    /* 1 if array parameter, 0 otherwise */
            struct ASTNode* next;           /* Next parameter */
        } param;

        /* Function call structure (NODE_FUNC_CALL) */
        struct {
            char* name;                     /* Function name */
            struct ASTNode* args;           /* Argument list */
        } funcCall;

        /* Return statement structure (NODE_RETURN) */
        struct {
            struct ASTNode* value;          /* Return value expression */
        } returnStmt;

        /* If statement structure (NODE_IF) */
        struct {
            struct ASTNode* condition;      /* Condition expression */
            struct ASTNode* thenStmt;       /* Statement to execute if true */
            struct ASTNode* elseStmt;       /* Statement to execute if false (can be NULL) */
        } ifStmt;
    } data;
} ASTNode;

/* AST CONSTRUCTION FUNCTIONS
 * These functions are called by the parser to build the tree
 */
ASTNode* createNum(int value);                                   /* Create number node */
ASTNode* createFloatNum(float value);                            /* Create float number node */
ASTNode* createVar(char* name);                                  /* Create variable node */
ASTNode* createBinOp(char op, ASTNode* left, ASTNode* right);   /* Create binary op node */
ASTNode* createCompareOp(int op, ASTNode* left, ASTNode* right); /* Create comparison op node */
ASTNode* createStringLit(char* s);                               /* Create string literal node */
ASTNode* createDecl(char* name);                                /* Create declaration node */
ASTNode* createFloatDecl(char* name);                           /* Create float declaration node */
ASTNode* createStrDecl(char* name);                             /* Create string declaration node */
/* Add new functions here*/
ASTNode* createAssign(char* var, ASTNode* value);               /* Create assignment node */
ASTNode* createPrint(ASTNode* expr);                            /* Create print node */
ASTNode* createInput();                                         /* Create input node */
ASTNode* createStmtList(ASTNode* stmt1, ASTNode* stmt2);        /* Create statement list */

ASTNode* createArrayDecl(char* name, int size);                 /* Create array declaration node */
ASTNode* createFloatArrayDecl(char* name, int size);             /* Create float array declaration node */
ASTNode* createArrayAssign(char* name, ASTNode* index, ASTNode* value); /* Create array assignment node */
ASTNode* createArrayAccess(char* name, ASTNode* index);          /* Create array access node */

/* Function-related AST construction functions */
ASTNode* createFuncDecl(char* name, ASTNode* params, ASTNode* body); /* Create function declaration node */
ASTNode* createParam(char* name, char* type);                    /* Create parameter node */
ASTNode* addParam(ASTNode* list, char* name, char* type);        /* Add parameter to list */
ASTNode* createArrayParam(char* name, char* type);               /* Create array parameter node */
ASTNode* addArrayParam(ASTNode* list, char* name, char* type);   /* Add array parameter to list */
ASTNode* createFuncCall(char* name, ASTNode* args);              /* Create function call node */
ASTNode* createReturn(ASTNode* value);                           /* Create return statement node */

/* If statement AST construction function */
ASTNode* createIfNode(ASTNode* condition, ASTNode* thenStmt, ASTNode* elseStmt); /* Create if statement node */

/* AST DISPLAY FUNCTION */
void printAST(ASTNode* node, int level);                        /* Pretty-print the AST */

#endif