%{
/* LEXICAL ANALYZER (SCANNER)
 * This is the first phase of compilation - breaking input into tokens
 * Flex generates a scanner from these rules that reads character by character
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "parser.tab.h"  /* Token definitions from Bison */
%}

/* Flex options to suppress warnings for unused functions */
%option nounput
%option noinput

%%

"int"           { return INT; }
"float"         { return FLOAT; }
"print"         { return PRINT; }
"string"        { return STRING; }
"return"        { return RETURN; }
"void"          { return VOID; }
"if"            { return IF; }
"else"          { return ELSE; }

[a-zA-Z_][a-zA-Z0-9_]* { 
    yylval.str = strdup(yytext);
    return ID; 
}

  /* it matches a quoted token, strips the quotes, allocates a heap buffer (malloc/strdup) and stores it in yylval.str.
  *the lexer allocates a temporary buffer, and the parser frees it after the AST node is created.
  */
"\""[^"]*"\""    {
    /* match a double-quoted string, copy without quotes */
    int len = yyleng;
    if (len >= 2) {
        char *s = malloc(len-1);
        strncpy(s, yytext+1, len-2);
        s[len-2] = '\0';
        yylval.str = s;
        return STRING_LITERAL;
    }
}

[0-9]+\.[0-9]+  {
    yylval.fnum = atof(yytext);
    return FLOAT_NUM;
}

[0-9]+          {
    yylval.num = atoi(yytext);
    return NUM;
}

"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }
"/"             { return '/'; }
"="             { return '='; }
"=="            { return EQ; }
"!="            { return NE; }
"<="            { return LE; }
">="            { return GE; }
"<"             { return '<'; }
">"             { return '>'; }
";"             { return ';'; }
"("             { return '('; }
")"             { return ')'; }
"]"             { return ']'; }
"["             { return '['; }
","             { return ','; }
"{"             { return '{'; }
"}"             { return '}'; }
"#"             { return FUNCTION; }

"//".*          { /* Skip single-line comments */ }
[ \t\n]         { }

.               { printf("Lexical Error: Unknown character '%c'\n", *yytext); }

%%

/* Required by Flex - signals end of input */
int yywrap() {
    return 1;  /* 1 means no more input files */
}