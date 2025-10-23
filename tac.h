#ifndef TAC_H
#define TAC_H

#include "ast.h"

/* THREE-ADDRESS CODE (TAC)
 * Intermediate representation between AST and machine code
 * Each instruction has at most 3 operands (result = arg1 op arg2)
 * Makes optimization and code generation easier
 */

/* TAC INSTRUCTION TYPES */
typedef enum {
    TAC_ADD,     /* Addition: result = arg1 + arg2 */
    TAC_SUB,     /* Subtraction: result = arg1 - arg2 */
    TAC_MUL,     /* Multiplication: result = arg1 * arg2 */
    TAC_DIV,     /* Division: result = arg1 / arg2 */
    TAC_ASSIGN,  /* Assignment: result = arg1 */
    TAC_PRINT,   /* Print: print(arg1) */
    TAC_DECL,     /* Declaration: declare result */
    TAC_ARRAY_DECL,    /* Array declaration: declare array[size] */
    TAC_ARRAY_ASSIGN,  /* Array assignment: array[index] = value */
    TAC_ARRAY_ACCESS,   /* Array access: temp = array[index] */
    TAC_LABEL,          /* Function entry point: LABEL func_name */
    TAC_PARAM,          /* Pass parameter: PARAM arg */
    TAC_CALL,           /* Function call: result = CALL func_name, num_params */
    TAC_RETURN,         /* Return value: RETURN value */
    TAC_FUNC_BEGIN,     /* Mark function start: FUNC_BEGIN name */
    TAC_FUNC_END        /* Mark function end: FUNC_END name */
} TACOp;

/* TAC INSTRUCTION STRUCTURE */
typedef struct TACInstr {
    TACOp op;               /* Operation type */
    char* arg1;             /* First operand (if needed) */
    char* arg2;             /* Second operand (for binary ops) */
    char* result;           /* Result/destination */
    int paramCount;  // For CALL instruction: number of params
    struct TACInstr* next;  /* Linked list pointer */
} TACInstr;

/* TAC LIST MANAGEMENT */
typedef struct {
    TACInstr* head;    /* First instruction */
    TACInstr* tail;    /* Last instruction (for efficient append) */
    int tempCount;     /* Counter for temporary variables (t0, t1, ...) */
} TACList;

/* TAC GENERATION FUNCTIONS */
void initTAC();                                                    /* Initialize TAC lists */
char* newTemp();                                                   /* Generate new temp variable */
TACInstr* createTAC(TACOp op, char* arg1, char* arg2, char* result); /* Create TAC instruction */
void appendTAC(TACInstr* instr);                                  /* Add instruction to list */
void generateTAC(ASTNode* node);                                  /* Convert AST to TAC */
char* generateTACExpr(ASTNode* node);                             /* Generate TAC for expression */

/* TAC OPTIMIZATION AND OUTPUT */
void printTAC();                                                   /* Display unoptimized TAC */
void optimizeTAC();                                                /* Apply optimizations */
void printOptimizedTAC();                                          /* Display optimized TAC */
void applyAdvancedOptimizations();                                 /* Apply advanced optimizations */

#endif