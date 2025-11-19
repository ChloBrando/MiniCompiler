/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUM = 258,
     FLOAT_NUM = 259,
     ID = 260,
     INT = 261,
     FLOAT = 262,
     PRINT = 263,
     INPUT = 264,
     VAR = 265,
     STRING = 266,
     FUNCTION = 267,
     RETURN = 268,
     VOID = 269,
     IF = 270,
     ELSE = 271,
     EQ = 272,
     NE = 273,
     LE = 274,
     GE = 275,
     STRING_LITERAL = 276
   };
#endif
/* Tokens.  */
#define NUM 258
#define FLOAT_NUM 259
#define ID 260
#define INT 261
#define FLOAT 262
#define PRINT 263
#define INPUT 264
#define VAR 265
#define STRING 266
#define FUNCTION 267
#define RETURN 268
#define VOID 269
#define IF 270
#define ELSE 271
#define EQ 272
#define NE 273
#define LE 274
#define GE 275
#define STRING_LITERAL 276




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 27 "parser.y"
{
    int num;                /* For integer literals */
    float fnum;             /* For float literals */
    char* str;              /* For identifiers */
    struct ASTNode* node;   /* For AST nodes */
}
/* Line 1529 of yacc.c.  */
#line 98 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

