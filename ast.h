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
    NODE_STR,       /* String literal (e.g., "hello") */
    NODE_STR_DECL,  /* String variable declaration (e.g., string s;) */
    NODE_VAR,       /* Variable reference (e.g., x) */
    NODE_BINOP,     /* Binary operation (e.g., x + y) */
    NODE_DECL,      /* Variable declaration (e.g., int x) */
    NODE_ASSIGN,    /* Assignment statement (e.g., x = 10) */
    NODE_PRINT,     /* Print statement (e.g., print(x)) */
    NODE_STMT_LIST,  /* List of statements (program structure) */
    NODE_ARRAY_DECL, /* Array declaration (e.g., int x[10]) */
    NODE_ARRAY_ASSIGN, /* Array element assignment (e.g., arr[2] = 5) */
    NODE_ARRAY_ACCESS, /* Array element access (e.g., arr[2]) */
    NODE_FUNC_DECL,   /* Function declaration (e.g., # add(int x) { ... }) */
    NODE_PARAM,       /* Function parameter */
    NODE_FUNC_CALL,   /* Function call (e.g., add(5, 3)) */
    NODE_RETURN       /* Return statement */
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
    /* String literal value (NODE_STR) */
    char* str;
        
        /* Variable or declaration name (NODE_VAR, NODE_DECL) */
        char* name;
        
        /* Binary operation structure (NODE_BINOP) */
        struct {
            char op;                    /* Operator character ('+') */
            struct ASTNode* left;       /* Left operand */
            struct ASTNode* right;      /* Right operand */
        } binop;
        
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
    } data;
} ASTNode;

/* AST CONSTRUCTION FUNCTIONS
 * These functions are called by the parser to build the tree
 */
ASTNode* createNum(int value);                                   /* Create number node */
ASTNode* createVar(char* name);                                  /* Create variable node */
ASTNode* createBinOp(char op, ASTNode* left, ASTNode* right);   /* Create binary op node */
ASTNode* createStringLit(char* s);                               /* Create string literal node */
ASTNode* createDecl(char* name);                                /* Create declaration node */
ASTNode* createStrDecl(char* name);                             /* Create string declaration node */
/* Add new functions here*/
ASTNode* createAssign(char* var, ASTNode* value);               /* Create assignment node */
ASTNode* createPrint(ASTNode* expr);                            /* Create print node */
ASTNode* createStmtList(ASTNode* stmt1, ASTNode* stmt2);        /* Create statement list */

ASTNode* createArrayDecl(char* name, int size);                 /* Create array declaration node */
ASTNode* createArrayAssign(char* name, ASTNode* index, ASTNode* value); /* Create array assignment node */
ASTNode* createArrayAccess(char* name, ASTNode* index);          /* Create array access node */

/* Function-related AST construction functions */
ASTNode* createFuncDecl(char* name, ASTNode* params, ASTNode* body); /* Create function declaration node */
ASTNode* createParam(char* name);                                /* Create parameter node */
ASTNode* addParam(ASTNode* list, char* name);                    /* Add parameter to list */
ASTNode* createFuncCall(char* name, ASTNode* args);              /* Create function call node */
ASTNode* createReturn(ASTNode* value);                           /* Create return statement node */

/* AST DISPLAY FUNCTION */
void printAST(ASTNode* node, int level);                        /* Pretty-print the AST */

#endif