# Lab Question 17

This document provides a detailed account of the production rules and modifications needed to add **while loop** support to the Mini Language Compiler.

## Overview

Adding while loops requires modifications across all compiler phases:
- Scanner (lexical analysis)
- Parser (syntax analysis) 
- AST (abstract syntax tree)
- Semantic analysis (type checking)
- Code generation (MIPS assembly)

---

## 1. Scanner Modifications (`scanner.l`)

Add the `while` keyword recognition to the lexical analyzer:

```lex
%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"
%}

%%

"int"           { return INT; }
"float"         { return FLOAT; }
"print"         { return PRINT; }
"string"        { return STRING; }
"return"        { return RETURN; }
"void"          { return VOID; }
"while"         { return WHILE; }     /* ADD THIS LINE */

/* ... rest of scanner rules ... */
```

### Additional Comparison Operators

For meaningful while loops, also add comparison operators:

```lex
"<"             { return '<'; }
">"             { return '>'; }
"<="            { return LE; }
">="            { return GE; }
"=="            { return EQ; }
"!="            { return NE; }
```

---

## 2. Parser Modifications (`parser.y`)

### Token Declarations

Add new tokens to the parser:

```yacc
%token INT FLOAT PRINT STRING RETURN VOID FUNCTION
%token WHILE EQ NE LE GE     /* ADD THESE TOKENS */
%token <num> NUM
%token <fnum> FLOAT_NUM
%token <str> ID STRING_LITERAL
```

### Operator Precedence

Define precedence for comparison operators:

```yacc
%left EQ NE             /* Equality operators */
%left '<' '>' LE GE     /* Relational operators */
%left '+' '-'           /* Addition/subtraction */
%left '*' '/'           /* Multiplication/division */
```

### Main While Loop Production Rule

```yacc
while_stmt: WHILE '(' expr ')' '{' stmt_list '}'
    {
        $$ = createWhileNode($3, $6);
    }
    | WHILE '(' expr ')' stmt
    {
        /* Single statement without braces */
        $$ = createWhileNode($3, $5);
    }
;
```

### Update Statement Rule

Modify the existing `stmt` rule to include while statements:

```yacc
stmt: decl          /* Variable declaration */
    | assign        /* Assignment statement */
    | print_stmt    /* Print statement */
    | func_decl     /* Function declaration */
    | while_stmt    /* ADD THIS LINE - While loop */
    | expr ';'      /* Expression statement */
    | RETURN expr ';' { $$ = createReturn($2); }
    | RETURN ';'      { $$ = createReturn(NULL); }
    | '{' stmt_list '}'  /* Compound statement */
;
```

### Enhanced Expression Rules

Add comparison operations for loop conditions:

```yacc
expr: NUM {
        $$ = createNum($1);
    }
    | FLOAT_NUM {
        $$ = createFloatNum($1);
    }
    | ID {
        $$ = createVar($1);
        free($1);
    }
    | expr '+' expr {
        $$ = createBinOp('+', $1, $3);
    }
    | expr '-' expr {
        $$ = createBinOp('-', $1, $3);
    }
    | expr '*' expr {
        $$ = createBinOp('*', $1, $3);
    }
    | expr '/' expr {
        $$ = createBinOp('/', $1, $3);
    }
    /* ADD COMPARISON OPERATORS */
    | expr '<' expr {
        $$ = createBinOp('<', $1, $3);
    }
    | expr '>' expr {
        $$ = createBinOp('>', $1, $3);
    }
    | expr EQ expr {
        $$ = createBinOp(EQ, $1, $3);
    }
    | expr NE expr {
        $$ = createBinOp(NE, $1, $3);
    }
    | expr LE expr {
        $$ = createBinOp(LE, $1, $3);
    }
    | expr GE expr {
        $$ = createBinOp(GE, $1, $3);
    }
    | '(' expr ')' {
        $$ = $2;
    }
;
```

---

## 3. AST Modifications (`ast.h`)

### Add While Loop Node Type

```c
typedef enum {
    NODE_NUM,           /* Numeric literal */
    NODE_FLOAT_NUM,     /* Float literal */
    NODE_STR,           /* String literal */
    NODE_VAR,           /* Variable reference */
    NODE_BINOP,         /* Binary operation */
    NODE_DECL,          /* Variable declaration */
    NODE_FLOAT_DECL,    /* Float declaration */
    NODE_ASSIGN,        /* Assignment statement */
    NODE_PRINT,         /* Print statement */
    NODE_STMT_LIST,     /* Statement list */
    NODE_WHILE,         /* ADD THIS - While loop */
    /* ... other existing node types ... */
} NodeType;
```

### Add While Loop Data Structure

Add to the ASTNode union:

```c
typedef struct ASTNode {
    NodeType type;
    
    union {
        /* ... existing data structures ... */
        
        /* While loop structure (NODE_WHILE) */
        struct {
            struct ASTNode* condition;   /* Loop condition */
            struct ASTNode* body;        /* Loop body */
        } whileLoop;
        
    } data;
} ASTNode;
```

### Function Declaration

Add the function prototype:

```c
/* While loop AST construction */
ASTNode* createWhileNode(ASTNode* condition, ASTNode* body);
```

---

## 4. AST Implementation (`ast.c`)

### While Loop Creation Function

```c
/* Create a while loop node */
ASTNode* createWhileNode(ASTNode* condition, ASTNode* body) {
    ASTNode* node = malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Error: Memory allocation failed for while node\n");
        exit(1);
    }
    
    node->type = NODE_WHILE;
    node->data.whileLoop.condition = condition;
    node->data.whileLoop.body = body;
    
    return node;
}
```

### Update Print AST Function

Add case for while loops in `printAST()`:

```c
void printAST(ASTNode* node, int level) {
    if (!node) return;

    /* Indent based on tree depth */
    for (int i = 0; i < level; i++) printf("  ");

    switch (node->type) {
        /* ... existing cases ... */
        
        case NODE_WHILE:
            printf("WHILE\n");
            printf("%*sCondition:\n", level * 2, "");
            printAST(node->data.whileLoop.condition, level + 1);
            printf("%*sBody:\n", level * 2, "");
            printAST(node->data.whileLoop.body, level + 1);
            break;
            
        /* ... other cases ... */
    }
}
```

---

## 5. Semantic Analysis (`semantic.c`)

### Type Checking for While Loops

Add case in semantic analysis function:

```c
int checkStmt(ASTNode* node) {
    if (!node) return 0;
    
    switch (node->type) {
        /* ... existing cases ... */
        
        case NODE_WHILE: {
            /* Check that condition is a valid expression */
            int conditionType = exprType(node->data.whileLoop.condition);
            if (conditionType == -1) {
                fprintf(stderr, "Semantic Error: Invalid while condition\n");
                return -1;
            }
            
            /* Check the loop body */
            int bodyResult = checkStmt(node->data.whileLoop.body);
            if (bodyResult == -1) {
                return -1;
            }
            
            return 0;
        }
        
        /* ... other cases ... */
    }
    
    return 0;
}
```

---

## 6. Code Generation (`codegen.c`)

### MIPS Assembly Generation

Add while loop code generation:

```c
static int labelCounter = 0;

int getNextLabel() {
    return ++labelCounter;
}

void generateStmt(ASTNode* node, FILE* output) {
    if (!node) return;
    
    switch (node->type) {
        /* ... existing cases ... */
        
        case NODE_WHILE: {
            int startLabel = getNextLabel();
            int endLabel = getNextLabel();
            
            /* Generate loop start label */
            fprintf(output, "while_start_%d:\n", startLabel);
            
            /* Generate condition evaluation */
            generateExpr(node->data.whileLoop.condition, output);
            
            /* Branch to end if condition is false */
            fprintf(output, "    beq $t0, $zero, while_end_%d\n", endLabel);
            
            /* Generate loop body */
            generateStmt(node->data.whileLoop.body, output);
            
            /* Jump back to condition check */
            fprintf(output, "    j while_start_%d\n", startLabel);
            
            /* Generate end label */
            fprintf(output, "while_end_%d:\n", endLabel);
            
            break;
        }
        
        /* ... other cases ... */
    }
}
```

### Comparison Operations in Expression Generation

Update expression generation for comparisons:

```c
void generateExpr(ASTNode* node, FILE* output) {
    switch (node->type) {
        /* ... existing cases ... */
        
        case NODE_BINOP: {
            /* Generate left operand */
            generateExpr(node->data.binop.left, output);
            fprintf(output, "    move $t1, $t0\n");
            
            /* Generate right operand */  
            generateExpr(node->data.binop.right, output);
            
            /* Perform operation based on operator */
            switch (node->data.binop.op) {
                case '+':
                    fprintf(output, "    add $t0, $t1, $t0\n");
                    break;
                case '-':
                    fprintf(output, "    sub $t0, $t1, $t0\n");
                    break;
                case '*':
                    fprintf(output, "    mul $t0, $t1, $t0\n");
                    break;
                case '/':
                    fprintf(output, "    div $t1, $t0\n");
                    fprintf(output, "    mflo $t0\n");
                    break;
                case '<':
                    fprintf(output, "    slt $t0, $t1, $t0\n");
                    break;
                case '>':
                    fprintf(output, "    slt $t0, $t0, $t1\n");
                    break;
                /* Add other comparison operators as needed */
            }
            break;
        }
        
        /* ... other cases ... */
    }
}
```

---

## 7. Example Usage

With these modifications, your compiler can handle while loops like:

```c
// Simple counting loop
int i;
i = 0;
while (i < 10) {
    print(i);
    i = i + 1;
}

// Loop with complex condition
int sum;
int count;
sum = 0;
count = 1;

while (count <= 100) {
    sum = sum + count;
    count = count + 1;
}
print("Sum of 1-100:");
print(sum);

// Nested loops
int row;
int col;
row = 0;

while (row < 3) {
    col = 0;
    while (col < 3) {
        print("Position:");
        print(row);
        print(col);
        col = col + 1;
    }
    row = row + 1;
}
```

---

## 8. Testing Strategy

### Test Cases to Implement

1. **Basic While Loop**
   ```c
   int i;
   i = 0;
   while (i < 5) {
       print(i);
       i = i + 1;
   }
   ```

2. **While Loop with Complex Condition**
   ```c
   int x;
   int y;
   x = 10;
   y = 20;
   while (x < y) {
       x = x + 2;
       y = y - 1;
   }
   ```

3. **Nested While Loops**
   ```c
   int outer;
   outer = 0;
   while (outer < 3) {
       int inner;
       inner = 0;
       while (inner < 2) {
           print(outer);
           print(inner);
           inner = inner + 1;
       }
       outer = outer + 1;
   }
   ```

### Compilation Test
```bash
./minicompiler test_while.c output.s
spim -file output.s
```

---

## 9. Summary of Required Production Rules

The key production rules needed:

1. **`while_stmt: WHILE '(' expr ')' '{' stmt_list '}'`**
2. **`while_stmt: WHILE '(' expr ')' stmt`** (single statement)
3. **Update `stmt` rule** to include `while_stmt`
4. **Enhanced `expr` rules** for comparison operations
5. **Proper operator precedence** for comparisons

These rules, combined with the supporting AST, semantic, and code generation functions, will provide complete while loop support for your compiler!

---

## 10. Implementation Checklist

- [ ] Add `WHILE` token to scanner.l
- [ ] Add comparison operator tokens (EQ, NE, LE, GE)
- [ ] Add while_stmt production rules to parser.y
- [ ] Update stmt rule to include while_stmt
- [ ] Add comparison expression rules
- [ ] Set proper operator precedence
- [ ] Add NODE_WHILE to AST node types
- [ ] Implement createWhileNode() function
- [ ] Update printAST() for while loops
- [ ] Add while loop semantic checking
- [ ] Implement while loop code generation
- [ ] Add comparison operation code generation
- [ ] Create comprehensive test cases
- [ ] Test compilation and execution

This comprehensive implementation will add robust while loop support to your Mini Language Compiler!