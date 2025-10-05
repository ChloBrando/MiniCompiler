%{
/* SYNTAX ANALYZER (PARSER)
 * This is the second phase of compilation - checking grammar rules
 * Bison generates a parser that builds an Abstract Syntax Tree (AST)
 * The parser uses tokens from the scanner to verify syntax is correct
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/* External declarations for lexer interface */
extern int yylex();      /* Get next token from scanner */
extern int yyparse();    /* Parse the entire input */
extern FILE* yyin;       /* Input file handle */

void yyerror(const char* s);  /* Error handling function */
ASTNode* root = NULL;          /* Root of the Abstract Syntax Tree */
%}

/* SEMANTIC VALUES UNION
 * Defines possible types for tokens and grammar symbols
 * This allows different grammar rules to return different data types
 */
%union {
    int num;                /* For integer literals */
    char* str;              /* For identifiers */
    struct ASTNode* node;   /* For AST nodes */
}

/* TOKEN DECLARATIONS with their semantic value types */
%token <num> NUM        /* Number token carries an integer value */
%token <str> ID         /* Identifier token carries a string */
%token INT PRINT VAR STRING        /* Keywords have no semantic value */
%token <str> STRING_LITERAL

/* NON-TERMINAL TYPES - Define what type each grammar rule returns */
%type <node> program stmt_list stmt decl assign expr print_stmt

/* OPERATOR PRECEDENCE AND ASSOCIATIVITY */
%left '+' '-' /* Addition is left-associative: a+b+c = (a+b)+c */

%%

/* GRAMMAR RULES - Define the structure of our language */

/* PROGRAM RULE - Entry point of our grammar */
program:
    stmt_list { 
        /* Action: Save the statement list as our AST root */
        root = $1;  /* $1 refers to the first symbol (stmt_list) */
    }
    ;

/* STATEMENT LIST - Handles multiple statements */
stmt_list:
    stmt { 
        /* Base case: single statement */
        $$ = $1;  /* Pass the statement up as-is */
    }
    | stmt_list stmt { 
        /* Recursive case: list followed by another statement */
        $$ = createStmtList($1, $2);  /* Build linked list of statements */
    }
    ;

/* STATEMENT TYPES - The three kinds of statements we support */
stmt:
    decl        /* Variable declaration */
    | assign    /* Assignment statement */
    | print_stmt /* Print statement */
    ;

/* DECLARATION RULE - "int x;" and "int x[NUM];" */
decl:
    INT ID ';' { 
                /* Create an AST node for an integer declaration.
                 * The lexer returned the identifier as a heap-allocated string
                 * (yylval.str = strdup(yytext)) so the parser receives ownership
                 * of that char* in $2. We pass the name into createDecl which
                 * copies or stores the name as needed in the AST, and then we
                 * free($2) here to avoid a temporary memory leak in the parser.
                 *
                 * Important: calling free() here does NOT "reserve stack space"
                 * or allocate runtime memory for the variable. The parser only
                 * builds the AST. Actual stack offsets and memory layout are
                 * created later by the semantic pass (symtab) when we call
                 * addVar/addArrayVar/addStringVar.
                 */
                $$ = createDecl($2);
                free($2);
    }
  | INT ID '[' NUM ']' ';' { 
                /* Build an AST node representing an array declaration.
                 * The NUM value ($4) is a compile-time constant for the size.
                 * The string $2 was allocated by the lexer and must be freed
                 * after the parser copies or consumes it. Again, no runtime
                 * memory is allocated here — this is purely syntactic AST work.
                 */
                $$ = createArrayDecl($2, $4);
                free($2);
    }
  | STRING ID ';' {
            /* String declaration: create AST node and free parser temp memory.
             * createStrDecl only records the intention to declare a string;
             * the semantic phase will actually register it in the symbol table
             * and assign a stack offset for runtime storage of a pointer.
             */
            $$ = createStrDecl($2);
            free($2);
    }
  ;

/* ASSIGNMENT RULE - "x = expr;" and "x[expr] = expr;" */
assign:
    ID '=' expr ';' { 
        $$ = createAssign($1, $3);
        free($1);
    }
  | ID '[' expr ']' '=' expr ';' { 
        $$ = createArrayAssign($1, $3, $6);
        free($1);
    }
  ;


/* EXPRESSION RULES - Build expression trees */
expr:
    NUM { 
        /* Literal number */
        $$ = createNum($1);  /* Create leaf node with number value */
    }
    | ID { 
        /* Variable reference */
        $$ = createVar($1);  /* Create leaf node with variable name */
        free($1);            /* Free the identifier string */
    }
    | STRING_LITERAL {
        /* String literal: the lexer allocated a C string and put it in $1.
         * createStringLit will create an AST node that typically copies
         * the pointer into the node structure (or copies the contents).
         * After creating the AST node we call free($1) to release the
         * temporary buffer allocated by the lexer. The AST owns whatever
         * it needs after this call.
         */
        $$ = createStringLit($1);
        free($1);
    }
    | expr '+' expr { 
        /* Addition operation - builds binary tree */
        $$ = createBinOp('+', $1, $3);  /* Left child, op, right child */
    }
    | expr '-' expr { 
        /* Subtraction operation */ 
        $$ = createBinOp('-', $1, $3);  /* Left child, op, right child */
    }
    | ID '[' expr ']' { 
        /* Array element access */
        $$ = createArrayAccess($1, $3);  /* $1=ID, $3=index expr */
        free($1);                         /* Free the identifier string */
    }
    ;

/* PRINT STATEMENT - "print(expr);" */
print_stmt:
    PRINT '(' expr ')' ';' { 
        /* Create print node with expression to print */
        $$ = createPrint($3);  /* $3 is the expression inside parens */
    }
    ;

%%

/* ERROR HANDLING - Called by Bison when syntax error detected */
void yyerror(const char* s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
}