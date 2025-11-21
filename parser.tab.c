/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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
     WHILE = 272,
     EQ = 273,
     NE = 274,
     LE = 275,
     GE = 276,
     STRING_LITERAL = 277
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
#define WHILE 272
#define EQ 273
#define NE 274
#define LE 275
#define GE 276
#define STRING_LITERAL 277




/* Copy the first part of user declarations.  */
#line 1 "parser.y"

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
extern int yylineno;     /* Line number from scanner */
extern char* yytext;     /* Current token text */

void yyerror(const char* s);  /* Error handling function */
ASTNode* root = NULL;          /* Root of the Abstract Syntax Tree */


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 27 "parser.y"
{
    int num;                /* For integer literals */
    float fnum;             /* For float literals */
    char* str;              /* For identifiers */
    struct ASTNode* node;   /* For AST nodes */
}
/* Line 193 of yacc.c.  */
#line 169 "parser.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 182 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  42
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   372

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  13
/* YYNRULES -- Number of rules.  */
#define YYNRULES  56
/* YYNRULES -- Number of states.  */
#define YYNSTATES  134

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   277

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      35,    36,    27,    25,    37,    26,     2,    28,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    29,
      23,    34,    24,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    32,     2,    33,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    30,     2,    31,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    16,    18,
      20,    22,    25,    29,    32,    36,    40,    44,    51,    58,
      62,    67,    75,    77,    79,    81,    83,    87,    91,    95,
      99,   103,   107,   111,   115,   119,   123,   127,   132,   136,
     141,   145,   151,   159,   168,   171,   174,   179,   184,   189,
     194,   201,   208,   210,   214,   220,   228
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    40,    -1,    41,    -1,    40,    41,    -1,
      42,    -1,    43,    -1,    45,    -1,    46,    -1,    49,    -1,
      50,    -1,    44,    29,    -1,    13,    44,    29,    -1,    13,
      29,    -1,    30,    40,    31,    -1,     6,     5,    29,    -1,
       7,     5,    29,    -1,     6,     5,    32,     3,    33,    29,
      -1,     7,     5,    32,     3,    33,    29,    -1,    11,     5,
      29,    -1,     5,    34,    44,    29,    -1,     5,    32,    44,
      33,    34,    44,    29,    -1,     3,    -1,     4,    -1,     5,
      -1,    22,    -1,    44,    25,    44,    -1,    44,    26,    44,
      -1,    44,    27,    44,    -1,    44,    28,    44,    -1,    44,
      23,    44,    -1,    44,    24,    44,    -1,    44,    18,    44,
      -1,    44,    19,    44,    -1,    44,    20,    44,    -1,    44,
      21,    44,    -1,    35,    44,    36,    -1,     5,    32,    44,
      33,    -1,     5,    35,    36,    -1,     5,    35,    48,    36,
      -1,     9,    35,    36,    -1,     8,    35,    44,    36,    29,
      -1,    12,     5,    35,    36,    30,    40,    31,    -1,    12,
       5,    35,    47,    36,    30,    40,    31,    -1,     6,     5,
      -1,     7,     5,    -1,     6,     5,    32,    33,    -1,     7,
       5,    32,    33,    -1,    47,    37,     6,     5,    -1,    47,
      37,     7,     5,    -1,    47,    37,     6,     5,    32,    33,
      -1,    47,    37,     7,     5,    32,    33,    -1,    44,    -1,
      48,    37,    44,    -1,    15,    35,    44,    36,    41,    -1,
      15,    35,    44,    36,    41,    16,    41,    -1,    17,    35,
      44,    36,    41,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    58,    58,    66,    70,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    92,    96,   100,   104,   108,
     116,   120,   128,   132,   136,   141,   145,   149,   153,   157,
     161,   165,   169,   173,   177,   181,   185,   189,   194,   199,
     204,   212,   220,   225,   234,   238,   242,   246,   250,   254,
     258,   262,   270,   273,   280,   284,   291
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "FLOAT_NUM", "ID", "INT", "FLOAT",
  "PRINT", "INPUT", "VAR", "STRING", "FUNCTION", "RETURN", "VOID", "IF",
  "ELSE", "WHILE", "EQ", "NE", "LE", "GE", "STRING_LITERAL", "'<'", "'>'",
  "'+'", "'-'", "'*'", "'/'", "';'", "'{'", "'}'", "'['", "']'", "'='",
  "'('", "')'", "','", "$accept", "program", "stmt_list", "stmt", "decl",
  "assign", "expr", "print_stmt", "func_decl", "param_list", "arg_list",
  "if_stmt", "while_stmt", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,    60,    62,    43,    45,    42,    47,    59,
     123,   125,    91,    93,    61,    40,    41,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    40,    40,    41,    41,    41,    41,    41,
      41,    41,    41,    41,    41,    42,    42,    42,    42,    42,
      43,    43,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    45,    46,    46,    47,    47,    47,    47,    47,    47,
      47,    47,    48,    48,    49,    49,    50
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     2,     3,     2,     3,     3,     3,     6,     6,     3,
       4,     7,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     4,     3,     4,
       3,     5,     7,     8,     2,     2,     4,     4,     4,     4,
       6,     6,     1,     3,     5,     7,     5
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    22,    23,    24,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    25,     0,     0,     0,     2,     3,     5,
       6,     0,     7,     8,     9,    10,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    24,    13,     0,     0,     0,
       0,     0,     1,     4,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    11,     0,     0,    38,    52,     0,
      15,     0,    16,     0,     0,    40,    19,     0,     0,    12,
       0,     0,    14,    36,    32,    33,    34,    35,    30,    31,
      26,    27,    28,    29,    37,    20,    39,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    53,
       0,     0,    41,    44,    45,     0,     0,     0,    37,    54,
      56,     0,    17,    18,     0,     0,     0,     0,     0,     0,
       0,    21,    46,    47,    42,     0,    48,    49,    55,    43,
       0,     0,    50,    51
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    94,
      59,    24,    25
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -22
static const yytype_int16 yypact[] =
{
     205,   -22,   -22,   -18,     7,    15,     5,    39,    26,    70,
       6,    42,    43,   -22,   205,    54,    81,   205,   -22,   -22,
     -22,   296,   -22,   -22,   -22,   -22,    54,    54,    51,   -11,
     -10,    54,    46,    59,    48,    -5,   -22,   308,    54,    54,
     106,   218,   -22,   -22,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,   -22,   274,   320,   -22,   344,    -3,
     -22,    87,   -22,    88,   232,   -22,   -22,    -4,    54,   -22,
     246,   260,   -22,   -22,    44,    44,   -21,   -21,   -21,   -21,
      11,    11,   -22,   -22,    50,   -22,   -22,    54,    60,    61,
      66,    92,    93,    71,    16,   285,   205,   205,    54,   344,
      73,    76,   -22,    68,    74,   205,    77,    55,   -22,   100,
     -22,   332,   -22,   -22,    89,    91,   139,   205,   115,   120,
     205,   -22,   -22,   -22,   -22,   172,    94,    95,   -22,   -22,
      96,    97,   -22,   -22
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -22,   -22,   -13,   -17,   -22,   -22,    -2,   -22,   -22,   -22,
     -22,   -22,   -22
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      43,    40,    91,    92,    50,    51,    52,    53,    37,     1,
       2,    35,    29,    41,    26,     7,    27,    28,    60,    62,
      30,    61,    63,    43,    55,    56,    58,    68,    13,    64,
      28,    33,    93,    86,    87,    36,    70,    71,    52,    53,
      31,    15,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,   106,   107,     1,     2,    35,     1,     2,    35,
       7,   118,   119,     7,    46,    47,    95,    48,    49,    50,
      51,    52,    53,    13,    32,    34,    13,    38,    39,   109,
     110,    42,    65,    67,    98,    99,    15,    57,    66,    15,
      88,    89,   116,   100,   101,   102,   111,   103,   104,    43,
     114,   105,   112,   128,   125,   113,   115,   117,    43,     1,
       2,     3,     4,     5,     6,     7,   120,     8,     9,    10,
     126,    11,   122,    12,   123,   127,   130,   131,    13,   132,
     133,     0,     0,     0,     0,     0,    14,    72,     0,     0,
       0,    15,     1,     2,     3,     4,     5,     6,     7,     0,
       8,     9,    10,     0,    11,     0,    12,     0,     0,     0,
       0,    13,     0,     0,     0,     0,     0,     0,     0,    14,
     124,     0,     0,     0,    15,     1,     2,     3,     4,     5,
       6,     7,     0,     8,     9,    10,     0,    11,     0,    12,
       0,     0,     0,     0,    13,     0,     0,     0,     0,     0,
       0,     0,    14,   129,     0,     0,     0,    15,     1,     2,
       3,     4,     5,     6,     7,     0,     8,     9,    10,     0,
      11,     0,    12,     0,     0,     0,     0,    13,     0,     0,
       0,     0,     0,     0,     0,    14,    44,    45,    46,    47,
      15,    48,    49,    50,    51,    52,    53,     0,     0,     0,
      44,    45,    46,    47,    73,    48,    49,    50,    51,    52,
      53,     0,     0,     0,    44,    45,    46,    47,    90,    48,
      49,    50,    51,    52,    53,     0,     0,     0,    44,    45,
      46,    47,    96,    48,    49,    50,    51,    52,    53,     0,
       0,     0,    44,    45,    46,    47,    97,    48,    49,    50,
      51,    52,    53,    44,    45,    46,    47,    84,    48,    49,
      50,    51,    52,    53,    44,    45,    46,    47,   108,    48,
      49,    50,    51,    52,    53,    54,    44,    45,    46,    47,
       0,    48,    49,    50,    51,    52,    53,    69,    44,    45,
      46,    47,     0,    48,    49,    50,    51,    52,    53,    85,
      44,    45,    46,    47,     0,    48,    49,    50,    51,    52,
      53,   121,    44,    45,    46,    47,     0,    48,    49,    50,
      51,    52,    53
};

static const yytype_int8 yycheck[] =
{
      17,    14,     6,     7,    25,    26,    27,    28,    10,     3,
       4,     5,     5,    15,    32,     9,    34,    35,    29,    29,
       5,    32,    32,    40,    26,    27,    28,    32,    22,    31,
      35,     5,    36,    36,    37,    29,    38,    39,    27,    28,
      35,    35,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    36,    37,     3,     4,     5,     3,     4,     5,
       9,     6,     7,     9,    20,    21,    68,    23,    24,    25,
      26,    27,    28,    22,    35,     5,    22,    35,    35,    96,
      97,     0,    36,    35,    34,    87,    35,    36,    29,    35,
       3,     3,   105,    33,    33,    29,    98,     5,     5,   116,
      32,    30,    29,   120,   117,    29,    32,    30,   125,     3,
       4,     5,     6,     7,     8,     9,    16,    11,    12,    13,
       5,    15,    33,    17,    33,     5,    32,    32,    22,    33,
      33,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,    -1,
      -1,    35,     3,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    -1,    15,    -1,    17,    -1,    -1,    -1,
      -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      31,    -1,    -1,    -1,    35,     3,     4,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    -1,    15,    -1,    17,
      -1,    -1,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    31,    -1,    -1,    -1,    35,     3,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    -1,
      15,    -1,    17,    -1,    -1,    -1,    -1,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    18,    19,    20,    21,
      35,    23,    24,    25,    26,    27,    28,    -1,    -1,    -1,
      18,    19,    20,    21,    36,    23,    24,    25,    26,    27,
      28,    -1,    -1,    -1,    18,    19,    20,    21,    36,    23,
      24,    25,    26,    27,    28,    -1,    -1,    -1,    18,    19,
      20,    21,    36,    23,    24,    25,    26,    27,    28,    -1,
      -1,    -1,    18,    19,    20,    21,    36,    23,    24,    25,
      26,    27,    28,    18,    19,    20,    21,    33,    23,    24,
      25,    26,    27,    28,    18,    19,    20,    21,    33,    23,
      24,    25,    26,    27,    28,    29,    18,    19,    20,    21,
      -1,    23,    24,    25,    26,    27,    28,    29,    18,    19,
      20,    21,    -1,    23,    24,    25,    26,    27,    28,    29,
      18,    19,    20,    21,    -1,    23,    24,    25,    26,    27,
      28,    29,    18,    19,    20,    21,    -1,    23,    24,    25,
      26,    27,    28
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    11,    12,
      13,    15,    17,    22,    30,    35,    39,    40,    41,    42,
      43,    44,    45,    46,    49,    50,    32,    34,    35,     5,
       5,    35,    35,     5,     5,     5,    29,    44,    35,    35,
      40,    44,     0,    41,    18,    19,    20,    21,    23,    24,
      25,    26,    27,    28,    29,    44,    44,    36,    44,    48,
      29,    32,    29,    32,    44,    36,    29,    35,    32,    29,
      44,    44,    31,    36,    44,    44,    44,    44,    44,    44,
      44,    44,    44,    44,    33,    29,    36,    37,     3,     3,
      36,     6,     7,    36,    47,    44,    36,    36,    34,    44,
      33,    33,    29,     5,     5,    30,    36,    37,    33,    41,
      41,    44,    29,    29,    32,    32,    40,    30,     6,     7,
      16,    29,    33,    33,    31,    40,     5,     5,    41,    31,
      32,    32,    33,    33
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 58 "parser.y"
    { 
        /* Action: Save the statement list as our AST root */
        root = (yyvsp[(1) - (1)].node);  /* $1 refers to the first symbol (stmt_list) */
    ;}
    break;

  case 3:
#line 66 "parser.y"
    { 
        /* Base case: single statement */
        (yyval.node) = (yyvsp[(1) - (1)].node);  /* Pass the statement up as-is */
    ;}
    break;

  case 4:
#line 70 "parser.y"
    { 
        /* Recursive case: list followed by another statement */
        (yyval.node) = createStmtList((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));  /* Build linked list of statements */
    ;}
    break;

  case 12:
#line 85 "parser.y"
    { (yyval.node) = createReturn((yyvsp[(2) - (3)].node)); ;}
    break;

  case 13:
#line 86 "parser.y"
    { (yyval.node) = createReturn(NULL); ;}
    break;

  case 14:
#line 87 "parser.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 15:
#line 92 "parser.y"
    {
                (yyval.node) = createDecl((yyvsp[(2) - (3)].str));
                free((yyvsp[(2) - (3)].str));
    ;}
    break;

  case 16:
#line 96 "parser.y"
    {
                (yyval.node) = createFloatDecl((yyvsp[(2) - (3)].str));
                free((yyvsp[(2) - (3)].str));
    ;}
    break;

  case 17:
#line 100 "parser.y"
    {
                (yyval.node) = createArrayDecl((yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].num));
                free((yyvsp[(2) - (6)].str));
    ;}
    break;

  case 18:
#line 104 "parser.y"
    {
                (yyval.node) = createFloatArrayDecl((yyvsp[(2) - (6)].str), (yyvsp[(4) - (6)].num));
                free((yyvsp[(2) - (6)].str));
    ;}
    break;

  case 19:
#line 108 "parser.y"
    {
            (yyval.node) = createStrDecl((yyvsp[(2) - (3)].str));
            free((yyvsp[(2) - (3)].str));
    ;}
    break;

  case 20:
#line 116 "parser.y"
    { 
        (yyval.node) = createAssign((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].node));
        free((yyvsp[(1) - (4)].str));
    ;}
    break;

  case 21:
#line 120 "parser.y"
    { 
        (yyval.node) = createArrayAssign((yyvsp[(1) - (7)].str), (yyvsp[(3) - (7)].node), (yyvsp[(6) - (7)].node));
        free((yyvsp[(1) - (7)].str));
    ;}
    break;

  case 22:
#line 128 "parser.y"
    {
        /* Literal number */
        (yyval.node) = createNum((yyvsp[(1) - (1)].num));  /* Create leaf node with number value */
    ;}
    break;

  case 23:
#line 132 "parser.y"
    {
        /* Literal float */
        (yyval.node) = createFloatNum((yyvsp[(1) - (1)].fnum));  /* Create leaf node with float value */
    ;}
    break;

  case 24:
#line 136 "parser.y"
    {
        /* Variable reference */
        (yyval.node) = createVar((yyvsp[(1) - (1)].str));  /* Create leaf node with variable name */
        free((yyvsp[(1) - (1)].str));            /* Free the identifier string */
    ;}
    break;

  case 25:
#line 141 "parser.y"
    {
        (yyval.node) = createStringLit((yyvsp[(1) - (1)].str));
        free((yyvsp[(1) - (1)].str));
    ;}
    break;

  case 26:
#line 145 "parser.y"
    {
        /* Addition operation - builds binary tree */
        (yyval.node) = createBinOp('+', (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));  /* Left child, op, right child */
    ;}
    break;

  case 27:
#line 149 "parser.y"
    {
        /* Subtraction operation */
        (yyval.node) = createBinOp('-', (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));  /* Left child, op, right child */
    ;}
    break;

  case 28:
#line 153 "parser.y"
    {
        /* Multiplication operation */
        (yyval.node) = createBinOp('*', (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    ;}
    break;

  case 29:
#line 157 "parser.y"
    {
        /* Division operation */
        (yyval.node) = createBinOp('/', (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    ;}
    break;

  case 30:
#line 161 "parser.y"
    {
        /* Less than comparison */
        (yyval.node) = createCompareOp('<', (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    ;}
    break;

  case 31:
#line 165 "parser.y"
    {
        /* Greater than comparison */
        (yyval.node) = createCompareOp('>', (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    ;}
    break;

  case 32:
#line 169 "parser.y"
    {
        /* Equality comparison */
        (yyval.node) = createCompareOp(EQ, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    ;}
    break;

  case 33:
#line 173 "parser.y"
    {
        /* Not equal comparison */
        (yyval.node) = createCompareOp(NE, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    ;}
    break;

  case 34:
#line 177 "parser.y"
    {
        /* Less than or equal comparison */
        (yyval.node) = createCompareOp(LE, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    ;}
    break;

  case 35:
#line 181 "parser.y"
    {
        /* Greater than or equal comparison */
        (yyval.node) = createCompareOp(GE, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    ;}
    break;

  case 36:
#line 185 "parser.y"
    {
        /* Parenthesized expression */
        (yyval.node) = (yyvsp[(2) - (3)].node);
    ;}
    break;

  case 37:
#line 189 "parser.y"
    { 
        /* Array element access */
        (yyval.node) = createArrayAccess((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].node));  /* $1=ID, $3=index expr */
        free((yyvsp[(1) - (4)].str));                         /* Free the identifier string */
    ;}
    break;

  case 38:
#line 194 "parser.y"
    { 
        /* Function call with no arguments */
        (yyval.node) = createFuncCall((yyvsp[(1) - (3)].str), NULL);
        free((yyvsp[(1) - (3)].str));
    ;}
    break;

  case 39:
#line 199 "parser.y"
    {
        /* Function call with arguments */
        (yyval.node) = createFuncCall((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].node));
        free((yyvsp[(1) - (4)].str));
    ;}
    break;

  case 40:
#line 204 "parser.y"
    {
        /* Input statement - reads integer from user */
        (yyval.node) = createInput();
    ;}
    break;

  case 41:
#line 212 "parser.y"
    { 
        /* Create print node with expression to print */
        (yyval.node) = createPrint((yyvsp[(3) - (5)].node));  /* $3 is the expression inside parens */
    ;}
    break;

  case 42:
#line 220 "parser.y"
    {
        /* Function with no parameters */
        (yyval.node) = createFuncDecl((yyvsp[(2) - (7)].str), NULL, (yyvsp[(6) - (7)].node));
        free((yyvsp[(2) - (7)].str));
    ;}
    break;

  case 43:
#line 225 "parser.y"
    {
        /* Function with parameters */
        (yyval.node) = createFuncDecl((yyvsp[(2) - (8)].str), (yyvsp[(4) - (8)].node), (yyvsp[(7) - (8)].node));
        free((yyvsp[(2) - (8)].str));
    ;}
    break;

  case 44:
#line 234 "parser.y"
    {
        (yyval.node) = createParam((yyvsp[(2) - (2)].str), "int");
        free((yyvsp[(2) - (2)].str));
    ;}
    break;

  case 45:
#line 238 "parser.y"
    {
        (yyval.node) = createParam((yyvsp[(2) - (2)].str), "float");
        free((yyvsp[(2) - (2)].str));
    ;}
    break;

  case 46:
#line 242 "parser.y"
    {
        (yyval.node) = createArrayParam((yyvsp[(2) - (4)].str), "int");
        free((yyvsp[(2) - (4)].str));
    ;}
    break;

  case 47:
#line 246 "parser.y"
    {
        (yyval.node) = createArrayParam((yyvsp[(2) - (4)].str), "float");
        free((yyvsp[(2) - (4)].str));
    ;}
    break;

  case 48:
#line 250 "parser.y"
    {
        (yyval.node) = addParam((yyvsp[(1) - (4)].node), (yyvsp[(4) - (4)].str), "int");
        free((yyvsp[(4) - (4)].str));
    ;}
    break;

  case 49:
#line 254 "parser.y"
    {
        (yyval.node) = addParam((yyvsp[(1) - (4)].node), (yyvsp[(4) - (4)].str), "float");
        free((yyvsp[(4) - (4)].str));
    ;}
    break;

  case 50:
#line 258 "parser.y"
    {
        (yyval.node) = addArrayParam((yyvsp[(1) - (6)].node), (yyvsp[(4) - (6)].str), "int");
        free((yyvsp[(4) - (6)].str));
    ;}
    break;

  case 51:
#line 262 "parser.y"
    {
        (yyval.node) = addArrayParam((yyvsp[(1) - (6)].node), (yyvsp[(4) - (6)].str), "float");
        free((yyvsp[(4) - (6)].str));
    ;}
    break;

  case 52:
#line 270 "parser.y"
    { 
        (yyval.node) = (yyvsp[(1) - (1)].node); 
    ;}
    break;

  case 53:
#line 273 "parser.y"
    { 
        (yyval.node) = createStmtList((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));  /* Reuse stmt_list structure for args */
    ;}
    break;

  case 54:
#line 280 "parser.y"
    {
        /* Simple if statement */
        (yyval.node) = createIfNode((yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), NULL);
    ;}
    break;

  case 55:
#line 284 "parser.y"
    {
        /* If-else statement */
        (yyval.node) = createIfNode((yyvsp[(3) - (7)].node), (yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node));
    ;}
    break;

  case 56:
#line 291 "parser.y"
    {
        /* While loop statement */
        (yyval.node) = createWhileNode((yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node));
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 1908 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 297 "parser.y"


/* ERROR HANDLING - Called by Bison when syntax error detected */
void yyerror(const char* s) {
    fprintf(stderr, "\n");
    fprintf(stderr, "╔════════════════════════════════════════════════════════════╗\n");
    fprintf(stderr, "║                     SYNTAX ERROR DETECTED                  ║\n");
    fprintf(stderr, "╚════════════════════════════════════════════════════════════╝\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Error at line %d near token: '%s'\n", yylineno, yytext);
    fprintf(stderr, "Error message: %s\n", s);
    fprintf(stderr, "\n");
    fprintf(stderr, "Common causes:\n");
    fprintf(stderr, "  • Missing semicolon ';' after statement\n");
    fprintf(stderr, "  • Mismatched parentheses () or braces {}\n");
    fprintf(stderr, "  • Invalid function syntax (use: # funcName(params) { })\n");
    fprintf(stderr, "  • Array parameters not supported (use: int x, not int x[])\n");
    fprintf(stderr, "  • Missing return type or parameters in function\n");
    fprintf(stderr, "\n");
}
