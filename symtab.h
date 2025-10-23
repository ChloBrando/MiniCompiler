#ifndef SYMTAB_H
#define SYMTAB_H

/* SYMBOL TABLE
 * Tracks all declared variables during compilation
 * Maps variable names to their memory locations (stack offsets)
 * Used for semantic checking and code generation
 */

#define MAX_VARS 100  /* Maximum number of variables supported */

/* SYMBOL ENTRY - Information about each variable */
typedef struct {
    char* name;     /* Variable identifier */
    int offset;     /* Stack offset in bytes (for MIPS stack frame) */
    int isArray;    /* Flag indicating if variable is an array (1=yes, 0=no) */
    int arraySize;  /* Size of the array if isArray is 1, */
    int type;       /* 0=int, 1=string, 2=float */
    int isFunction;  // 1 if this is a function, 0 if variable
    int paramCount;  // Number of parameters (if function)
    char** paramTypes; // Array of parameter types

} Symbol;

// Scope structure
typedef struct Scope {
    Symbol vars[MAX_VARS];
    int count;
    int nextOffset;
    struct Scope* parent;  // Link to enclosing scope
} Scope;

// Symbol table with scope stack
typedef struct {
    Scope* currentScope;   // Top of scope stack
    Scope* globalScope;    // Always points to global
} SymbolTable;

/* SYMBOL TABLE OPERATIONS */
void initSymTab();               /* Initialize empty symbol table */
int addVar(char* name);          /* Add new variable (int), returns offset or -1 if duplicate */
int addFloatVar(char* name);     /* Add new variable (float), returns offset or -1 if duplicate */
int addStringVar(char* name);    /* Add new variable (string), returns offset or -1 if duplicate */
int getVarOffset(char* name);    /* Get stack offset for variable, -1 if not found */
int isVarDeclared(char* name);   /* Check if variable exists (1=yes, 0=no) */
int addArrayVar(char* name, int size); /* Add new array variable, returns offset or -1 if duplicate */
int isArrayVar(char* name);      /* Check if variable is an array (1=yes, 0=no) */
int getArraySize(char* name); /* Get size of array variable, -1 if not found or not an array */
int isStringVar(char* name);    /* Check if variable is a string (1=yes, 0=no) */
int isFloatVar(char* name);     /* Check if variable is a float (1=yes, 0=no) */

void enterScope();              // Push new scope (entering function)
void exitScope();               // Pop scope (leaving function)
int addFunction(char* name, char* returnType,
                char** paramTypes, int paramCount);
int addParameter(char* name, char* type);
Symbol* lookupSymbol(char* name);  // Search current + parent scopes
int isInCurrentScope(char* name);  // Check only current scope
#endif