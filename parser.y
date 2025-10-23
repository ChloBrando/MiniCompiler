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
    float fnum;             /* For float literals */
    char* str;              /* For identifiers */
    struct ASTNode* node;   /* For AST nodes */
}

/* TOKEN DECLARATIONS with their semantic value types */
%token <num> NUM        /* Number token carries an integer value */
%token <fnum> FLOAT_NUM /* Float token carries a float value */
%token <str> ID         /* Identifier token carries a string */
%token INT FLOAT PRINT VAR STRING FUNCTION RETURN VOID
%token <str> STRING_LITERAL

/* NON-TERMINAL TYPES - Define what type each grammar rule returns */
%type <node> program stmt_list stmt decl assign expr print_stmt func_decl param_list arg_list

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

/* STATEMENT TYPES - NOW INCLUDING FUNCTIONS */
stmt:
    decl        /* Variable declaration */
    | assign    /* Assignment statement */
    | print_stmt /* Print statement */
    | func_decl  /* Function declaration */
    | expr ';'   /* Expression statement (for function calls) */
    | RETURN expr ';' { $$ = createReturn($2); }  /* Return with value */
    | RETURN ';'      { $$ = createReturn(NULL); } /* Return void */
    ;

/* DECLARATION RULE - "int x;" and "int x[NUM];" and "float x;" */
decl:
    INT ID ';' {
                $$ = createDecl($2);
                free($2);
    }
  | FLOAT ID ';' {
                $$ = createFloatDecl($2);
                free($2);
    }
  | INT ID '[' NUM ']' ';' {
                $$ = createArrayDecl($2, $4);
                free($2);
    }
  | STRING ID ';' {
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
    | FLOAT_NUM {
        /* Literal float */
        $$ = createFloatNum($1);  /* Create leaf node with float value */
    }
    | ID {
        /* Variable reference */
        $$ = createVar($1);  /* Create leaf node with variable name */
        free($1);            /* Free the identifier string */
    }
    | STRING_LITERAL {
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
    | expr '*' expr {
        /* Multiplication operation */
        $$ = createBinOp('*', $1, $3);
    }
    | expr '/' expr {
        /* Division operation */
        $$ = createBinOp('/', $1, $3);
    }
    | ID '[' expr ']' { 
        /* Array element access */
        $$ = createArrayAccess($1, $3);  /* $1=ID, $3=index expr */
        free($1);                         /* Free the identifier string */
    }
    | ID '(' ')' { 
        /* Function call with no arguments */
        $$ = createFuncCall($1, NULL);
        free($1);
    }
    | ID '(' arg_list ')' { 
        /* Function call with arguments */
        $$ = createFuncCall($1, $3);
        free($1);
    }
    ;

/* PRINT STATEMENT - "print(expr);" */
print_stmt:
    PRINT '(' expr ')' ';' { 
        /* Create print node with expression to print */
        $$ = createPrint($3);  /* $3 is the expression inside parens */
    }
    ;

/* FUNCTION DECLARATION - "# funcName() { ... }" */
func_decl:
    FUNCTION ID '(' ')' '{' stmt_list '}' {
        /* Function with no parameters */
        $$ = createFuncDecl($2, NULL, $6);
        free($2);
    }
    | FUNCTION ID '(' param_list ')' '{' stmt_list '}' {
        /* Function with parameters */
        $$ = createFuncDecl($2, $4, $7);
        free($2);
    }
    ;

/* PARAMETER LIST - "int x" or "float x" or "int x, float y, ..." */
param_list:
    INT ID {
        $$ = createParam($2, "int");
        free($2);
    }
    | FLOAT ID {
        $$ = createParam($2, "float");
        free($2);
    }
    | param_list ',' INT ID {
        $$ = addParam($1, $4, "int");
        free($4);
    }
    | param_list ',' FLOAT ID {
        $$ = addParam($1, $4, "float");
        free($4);
    }
    ;

/* ARGUMENT LIST - "expr" or "expr, expr, ..." */
arg_list:
    expr { 
        $$ = $1; 
    }
    | arg_list ',' expr { 
        $$ = createStmtList($1, $3);  /* Reuse stmt_list structure for args */
    }
    ;

%%

/* ERROR HANDLING - Called by Bison when syntax error detected */
void yyerror(const char* s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
}