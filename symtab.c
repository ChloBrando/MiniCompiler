/* SYMBOL TABLE IMPLEMENTATION
 * Manages variable declarations and lookups
 * Essential for semantic analysis (checking if variables are declared)
 * Provides memory layout information for code generation
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

/* Compile-time flag: set to 1 to enable symbol-table debug printing */
#ifndef SYMTAB_DEBUG
#define SYMTAB_DEBUG 0
#endif

/* Internal forward declaration for the debug print function (file-local) */
static void printSymTab(void);

/* Global symbol table instance */
SymbolTable symtab;

/* Initialize an empty symbol table */
void initSymTab() {
    /* Create the global scope (level 0) */
    Scope* globalScope = malloc(sizeof(Scope));
    globalScope->count = 0;
    globalScope->nextOffset = 0;
    globalScope->parent = NULL;  /* Global has no parent */

    /* Initialize symbol table with global scope */
    symtab.currentScope = globalScope;
    symtab.globalScope = globalScope;

#if SYMTAB_DEBUG
    printf("SYMBOL TABLE: Initialized with global scope\n");
    printSymTab();
#endif
}

/* Enter a new scope (e.g., when entering a function) */
void enterScope() {
    Scope* newScope = malloc(sizeof(Scope));
    newScope->count = 0;
    newScope->nextOffset = 0;  /* Local variables start at offset 0 */
    newScope->parent = symtab.currentScope;  /* Link to enclosing scope */

    symtab.currentScope = newScope;  /* Make it the active scope */

#if SYMTAB_DEBUG
    printf("SYMBOL TABLE: Entered new scope\n");
    printSymTab();
#endif
}

/* Exit the current scope (e.g., when leaving a function) */
void exitScope() {
    if (symtab.currentScope == symtab.globalScope) {
        fprintf(stderr, "SYMBOL TABLE ERROR: Cannot exit global scope\n");
        return;
    }

    Scope* oldScope = symtab.currentScope;
    symtab.currentScope = symtab.currentScope->parent;  /* Return to parent scope */

#if SYMTAB_DEBUG
    printf("SYMBOL TABLE: Exited scope (freed %d local variables)\n", oldScope->count);
#endif

    /* Free memory for the old scope */
    for (int i = 0; i < oldScope->count; i++) {
        free(oldScope->vars[i].name);
        if (oldScope->vars[i].isFunction && oldScope->vars[i].paramTypes) {
            for (int j = 0; j < oldScope->vars[i].paramCount; j++) {
                free(oldScope->vars[i].paramTypes[j]);
            }
            free(oldScope->vars[i].paramTypes);
        }
    }
    free(oldScope);

#if SYMTAB_DEBUG
    printSymTab();
#endif
}

/* Check if a variable is declared in the CURRENT scope only (for duplicate detection) */
int isInCurrentScope(char* name) {
    Scope* scope = symtab.currentScope;
    for (int i = 0; i < scope->count; i++) {
        if (strcmp(scope->vars[i].name, name) == 0) {
            return 1;  /* Found in current scope */
        }
    }
    return 0;  /* Not in current scope */
}

/* Add a new variable to the symbol table */
int addVar(char* name) {
    /* Check for duplicate declaration IN CURRENT SCOPE ONLY */
    if (isInCurrentScope(name)) {
#if SYMTAB_DEBUG
        printf("SYMBOL TABLE: Failed to add '%s' - already declared in current scope\n", name);
#endif
        return -1;  /* Error: variable already exists in current scope */
    }

    /* Get current scope */
    Scope* scope = symtab.currentScope;

    /* Add new symbol entry to current scope */
    scope->vars[scope->count].name = strdup(name);
    scope->vars[scope->count].offset = scope->nextOffset;
    scope->vars[scope->count].type = 0; /* int type */
    scope->vars[scope->count].isArray = 0;
    scope->vars[scope->count].arraySize = 0;
    scope->vars[scope->count].isFunction = 0;
    scope->vars[scope->count].paramCount = 0;
    scope->vars[scope->count].paramTypes = NULL;

    /* Advance offset by 4 bytes (size of int in MIPS) */
    int offset = scope->nextOffset;
    scope->nextOffset += 4;
    scope->count++;

#if SYMTAB_DEBUG
    printf("SYMBOL TABLE: Added variable '%s' at offset %d\n", name, offset);
    printSymTab();
#endif

    /* Return the offset for this variable */
    return offset;
}

int addFloatVar(char* name) {
    /* Check for duplicate declaration IN CURRENT SCOPE ONLY */
    if (isInCurrentScope(name)) {
#if SYMTAB_DEBUG
        printf("SYMBOL TABLE: Failed to add '%s' - already declared in current scope\n", name);
#endif
        return -1;
    }

    /* Get current scope */
    Scope* scope = symtab.currentScope;

    /* Add new float variable to current scope */
    scope->vars[scope->count].name = strdup(name);
    scope->vars[scope->count].offset = scope->nextOffset;
    scope->vars[scope->count].isArray = 0;
    scope->vars[scope->count].arraySize = 0;
    scope->vars[scope->count].type = 2; /* float type */
    scope->vars[scope->count].isFunction = 0;
    scope->vars[scope->count].paramCount = 0;
    scope->vars[scope->count].paramTypes = NULL;

    int offset = scope->nextOffset;
    scope->nextOffset += 4; /* float size */
    scope->count++;

#if SYMTAB_DEBUG
    printf("SYMBOL TABLE: Added float variable '%s' at offset %d\n", name, offset);
    printSymTab();
#endif
    return offset;
}

int addStringVar(char* name) {
    /* Check for duplicate declaration IN CURRENT SCOPE ONLY */
    if (isInCurrentScope(name)) {
#if SYMTAB_DEBUG
        printf("SYMBOL TABLE: Failed to add '%s' - already declared in current scope\n", name);
#endif
        return -1;
    }

    /* Get current scope */
    Scope* scope = symtab.currentScope;

    /* Add new string variable to current scope */
    scope->vars[scope->count].name = strdup(name);
    scope->vars[scope->count].offset = scope->nextOffset;
    scope->vars[scope->count].isArray = 0;
    scope->vars[scope->count].arraySize = 0;
    scope->vars[scope->count].type = 1; /* string type */
    scope->vars[scope->count].isFunction = 0;
    scope->vars[scope->count].paramCount = 0;
    scope->vars[scope->count].paramTypes = NULL;

    int offset = scope->nextOffset;
    scope->nextOffset += 4; /* pointer size */
    scope->count++;

#if SYMTAB_DEBUG
    printf("SYMBOL TABLE: Added string variable '%s' at offset %d\n", name, offset);
    printSymTab();
#endif
    return offset;
}

/* Look up a variable's stack offset */
int getVarOffset(char* name) {
    /* Use lookupSymbol to search current scope and all parent scopes */
    Symbol* sym = lookupSymbol(name);
    if (sym) {
#if SYMTAB_DEBUG
        printf("SYMBOL TABLE: Found variable '%s' at offset %d\n", name, sym->offset);
#endif
        return sym->offset;
    }
#if SYMTAB_DEBUG
    printf("SYMBOL TABLE: Variable '%s' not found\n", name);
#endif
    return -1;  /* Variable not found - semantic error */
}

/* Check if a variable has been declared (searches all scopes) */
int isVarDeclared(char* name) {
    return lookupSymbol(name) != NULL;  /* True if found in any scope */
}

int addArrayVar(char* name, int size) {
    /* Check for duplicate declaration IN CURRENT SCOPE ONLY */
    if (isInCurrentScope(name)) {
#if SYMTAB_DEBUG
        printf("SYMBOL TABLE: Failed to add array '%s' - already declared in current scope\n", name);
#endif
        return -1;
    }

    /* Get current scope */
    Scope* scope = symtab.currentScope;

    /* Add array entry to current scope */
    scope->vars[scope->count].name = strdup(name);
    scope->vars[scope->count].offset = scope->nextOffset;
    scope->vars[scope->count].isArray = 1;
    scope->vars[scope->count].arraySize = size;
    scope->vars[scope->count].type = 0; /* array of int */
    scope->vars[scope->count].isFunction = 0;
    scope->vars[scope->count].paramCount = 0;
    scope->vars[scope->count].paramTypes = NULL;

    /* Arrays need size * 4 bytes (4 bytes per int) */
    int offset = scope->nextOffset;
    scope->nextOffset += size * 4;
    scope->count++;

#if SYMTAB_DEBUG
    printf("SYMBOL TABLE: Added array '%s[%d]' at offset %d\n", name, size, offset);
    printSymTab();
#endif

    return offset;
}

/* Check if variable is an array */
int isArrayVar(char* name) {
    Symbol* sym = lookupSymbol(name);
    if (sym) {
        return sym->isArray;
    }
    return 0;  /* Not found or not an array */
}

/* Get array size */
int getArraySize(char* name) {
    Symbol* sym = lookupSymbol(name);
    if (sym) {
        return sym->arraySize;
    }
    return -1;  /* Not found */
}

/* Check if variable is a string */
int isStringVar(char* name) {
    Symbol* sym = lookupSymbol(name);
    if (sym) {
        return sym->type == 1;
    }
    return 0;  /* Not found or not a string */
}

/* Check if variable is a float */
int isFloatVar(char* name) {
    Symbol* sym = lookupSymbol(name);
    if (sym) {
        return sym->type == 2;
    }
    return 0;  /* Not found or not a float */
}

/* Add a function to the symbol table */
int addFunction(char* name, char* returnType, char** paramTypes, int paramCount) {
    /* Check for duplicate declaration IN CURRENT SCOPE ONLY */
    if (isInCurrentScope(name)) {
#if SYMTAB_DEBUG
        printf("SYMBOL TABLE: Failed to add function '%s' - already declared in current scope\n", name);
#endif
        return -1;
    }

    /* Get current scope */
    Scope* scope = symtab.currentScope;

    /* Add function entry to current scope */
    scope->vars[scope->count].name = strdup(name);
    scope->vars[scope->count].offset = -1;  /* Functions don't have stack offsets */
    scope->vars[scope->count].isArray = 0;
    scope->vars[scope->count].arraySize = 0;
    scope->vars[scope->count].type = 0;  /* Could be extended to track return type */
    scope->vars[scope->count].isFunction = 1;
    scope->vars[scope->count].paramCount = paramCount;

    /* Copy parameter types if provided */
    if (paramCount > 0 && paramTypes != NULL) {
        scope->vars[scope->count].paramTypes = malloc(sizeof(char*) * paramCount);
        for (int i = 0; i < paramCount; i++) {
            scope->vars[scope->count].paramTypes[i] = strdup(paramTypes[i]);
        }
    } else {
        scope->vars[scope->count].paramTypes = NULL;
    }

    scope->count++;

#if SYMTAB_DEBUG
    printf("SYMBOL TABLE: Added function '%s' with %d parameters\n", name, paramCount);
    printSymTab();
#endif

    return 0;  /* Success */
}

/* Add a parameter to the current scope (called when entering a function) */
int addParameter(char* name, char* type) {
    /* Parameters are just variables in the function's local scope */
    /* Now we properly track the type parameter */

    /* Check for duplicate parameter name IN CURRENT SCOPE ONLY */
    if (isInCurrentScope(name)) {
#if SYMTAB_DEBUG
        printf("SYMBOL TABLE: Failed to add parameter '%s' - already declared in current scope\n", name);
#endif
        return -1;
    }

    /* Get current scope */
    Scope* scope = symtab.currentScope;

    /* Determine type code: 0=int, 1=string, 2=float */
    int typeCode = 0;
    if (strcmp(type, "float") == 0) {
        typeCode = 2;
    } else if (strcmp(type, "string") == 0) {
        typeCode = 1;
    }

    /* Add parameter as a variable in current scope */
    scope->vars[scope->count].name = strdup(name);
    scope->vars[scope->count].offset = scope->nextOffset;
    scope->vars[scope->count].type = typeCode;
    scope->vars[scope->count].isArray = 0;
    scope->vars[scope->count].arraySize = 0;
    scope->vars[scope->count].isFunction = 0;
    scope->vars[scope->count].paramCount = 0;
    scope->vars[scope->count].paramTypes = NULL;

    int offset = scope->nextOffset;
    scope->nextOffset += 4;  /* Parameters take 4 bytes */
    scope->count++;

#if SYMTAB_DEBUG
    printf("SYMBOL TABLE: Added parameter '%s' (type=%s) at offset %d\n", name, type, offset);
    printSymTab();
#endif

    return offset;
}


/* Print current symbol table contents for debugging/tracing */
static void printSymTab() {
    printf("\n=== SYMBOL TABLE STATE ===\n");

    /* Walk through scopes from current to global */
    Scope* scope = symtab.currentScope;
    int scopeLevel = 0;

    /* First, determine how deep we are */
    Scope* temp = symtab.currentScope;
    while (temp != NULL) {
        scopeLevel++;
        temp = temp->parent;
    }
    scopeLevel--;  /* Convert count to 0-based level */

    /* Now print from current scope to global */
    int level = scopeLevel;
    while (scope != NULL) {
        if (scope == symtab.globalScope) {
            printf("GLOBAL SCOPE (level 0):\n");
        } else {
            printf("LOCAL SCOPE (level %d):\n", level);
        }
        printf("  Count: %d, Next Offset: %d\n", scope->count, scope->nextOffset);

        if (scope->count == 0) {
            printf("  (empty)\n");
        } else {
            for (int i = 0; i < scope->count; i++) {
                const char* typeName = scope->vars[i].type == 0 ? "int" :
                                       scope->vars[i].type == 1 ? "string" : "float";
                if (scope->vars[i].isFunction) {
                    printf("  [%d] FUNC %s(%d params) -> type=%s\n",
                        i, scope->vars[i].name, scope->vars[i].paramCount, typeName);
                } else if (scope->vars[i].isArray) {
                    printf("  [%d] %s[%d] -> offset %d, type=%s\n",
                        i, scope->vars[i].name, scope->vars[i].arraySize,
                        scope->vars[i].offset, typeName);
                } else {
                    printf("  [%d] %s -> offset %d, type=%s\n",
                        i, scope->vars[i].name, scope->vars[i].offset, typeName);
                }
            }
        }

        scope = scope->parent;
        level--;
        if (scope != NULL) {
            printf("  ^\n  | (parent)\n  |\n");
        }
    }

    printf("==========================\n\n");
}

Symbol* lookupSymbol(char* name) {
    Scope* scope = symtab.currentScope;

    // Search from current scope up to global
    while (scope != NULL) {
        for (int i = 0; i < scope->count; i++) {
            if (strcmp(scope->vars[i].name, name) == 0) {
                return &scope->vars[i];  // Found it
            }
        }
        scope = scope->parent;  // Try parent scope
    }
    return NULL;  // Not found in any scope
}
