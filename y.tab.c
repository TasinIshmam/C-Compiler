/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "1605115_parser.y" /* yacc.c:339  */

#include <bits/stdc++.h>
#define YYSTYPE SymbolInfo*
#include "1605115_symboltable.h"
#include "utilityfunctions.h"

using namespace std;

int yyparse(void);
int yylex(void);

extern FILE *yyin;

int line_no = 1;
int errorCount = 0;


//todo consider modifying this function. Might hit copychecker.

string outdecProcCode = " \nOUTDEC PROC  \n    PUSH AX \n    PUSH BX \n    PUSH CX \n    PUSH DX  \n    CMP AX,0 \n    JGE BEGIN \n    PUSH AX \n    MOV DL,'-' \n    MOV AH,2 \n    INT 21H \n    POP AX \n    NEG AX \n    \n    BEGIN: \n    XOR CX,CX \n    MOV BX,10 \n    \n    REPEAT: \n    XOR DX,DX \n    DIV BX \n    PUSH DX \n    INC CX \n    OR AX,AX \n    JNE REPEAT \n    MOV AH,2 \n    \n    PRINT_LOOP: \n    POP DX \n    ADD DL,30H \n    INT 21H \n    LOOP PRINT_LOOP \n    \n    MOV AH,2\n    MOV DL,10\n    INT 21H\n    \n    MOV DL,13\n    INT 21H\n	\n    POP DX \n    POP CX \n    POP BX \n    POP AX \n    ret \nOUTDEC ENDP\nEND MAIN\n";


bool functionScopeBeginFlag = false;

FILE *fp;
ofstream logfile;
ofstream scratchfile;
ofstream asmCodeFile;
SymbolTable symbolTable(10);


// vector<SymbolInfo*>para_list;
// vector<SymbolInfo*>arg_list;
// vector<SymbolInfo*>dec_list;


vector<string> variableDeclarationList;
vector<string> functionDelcarationList;
vector<pair<string,string> >arrayDeclarationList;




void yyerror(char *s) 
{
	string syntaxerror(s);
	logfile << "Error at line " << line_no <<" :" << syntaxerror << endl << endl ;
	errorCount++;
}



#line 119 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IF = 258,
    ELSE = 259,
    FOR = 260,
    WHILE = 261,
    DO = 262,
    BREAK = 263,
    INT = 264,
    FLOAT = 265,
    CHAR = 266,
    DOUBLE = 267,
    VOID = 268,
    RETURN = 269,
    SWITCH = 270,
    CASE = 271,
    DEFAULT = 272,
    CONTINUE = 273,
    CONST_INT = 274,
    CONST_FLOAT = 275,
    CONST_CHAR = 276,
    ADDOP = 277,
    MULOP = 278,
    INCOP = 279,
    RELOP = 280,
    ASSIGNOP = 281,
    LOGICOP = 282,
    BITOP = 283,
    NOT = 284,
    DECOP = 285,
    LPAREN = 286,
    RPAREN = 287,
    LCURL = 288,
    RCURL = 289,
    LTHIRD = 290,
    RTHIRD = 291,
    COMMA = 292,
    SEMICOLON = 293,
    STRING = 294,
    ID = 295,
    PRINTLN = 296,
    LOWER_THAN_ELSE = 297
  };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define FOR 260
#define WHILE 261
#define DO 262
#define BREAK 263
#define INT 264
#define FLOAT 265
#define CHAR 266
#define DOUBLE 267
#define VOID 268
#define RETURN 269
#define SWITCH 270
#define CASE 271
#define DEFAULT 272
#define CONTINUE 273
#define CONST_INT 274
#define CONST_FLOAT 275
#define CONST_CHAR 276
#define ADDOP 277
#define MULOP 278
#define INCOP 279
#define RELOP 280
#define ASSIGNOP 281
#define LOGICOP 282
#define BITOP 283
#define NOT 284
#define DECOP 285
#define LPAREN 286
#define RPAREN 287
#define LCURL 288
#define RCURL 289
#define LTHIRD 290
#define RTHIRD 291
#define COMMA 292
#define SEMICOLON 293
#define STRING 294
#define ID 295
#define PRINTLN 296
#define LOWER_THAN_ELSE 297

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 254 "y.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   145

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  122

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   297

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    73,    73,   110,   117,   126,   134,   141,   150,   164,
     178,   178,   221,   221,   252,   259,   266,   273,   283,   283,
     299,   299,   317,   330,   337,   344,   354,   361,   372,   379,
     388,   395,   404,   411,   418,   425,   436,   445,   456,   465,
     474,   483,   490,   499,   516,   550,   564,   576,   584,   595,
     603,   613,   621,   631,   639,   651,   681,   700,   713,   734,
     749,   760,   774,   787,   823,   857,   864,   873,   880
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "FOR", "WHILE", "DO",
  "BREAK", "INT", "FLOAT", "CHAR", "DOUBLE", "VOID", "RETURN", "SWITCH",
  "CASE", "DEFAULT", "CONTINUE", "CONST_INT", "CONST_FLOAT", "CONST_CHAR",
  "ADDOP", "MULOP", "INCOP", "RELOP", "ASSIGNOP", "LOGICOP", "BITOP",
  "NOT", "DECOP", "LPAREN", "RPAREN", "LCURL", "RCURL", "LTHIRD", "RTHIRD",
  "COMMA", "SEMICOLON", "STRING", "ID", "PRINTLN", "LOWER_THAN_ELSE",
  "$accept", "start", "program", "unit", "func_declaration",
  "func_definition", "$@1", "$@2", "parameter_list", "compound_statement",
  "$@3", "$@4", "var_declaration", "type_specifier", "declaration_list",
  "statements", "statement", "expression_statement", "variable",
  "expression", "logic_expression", "rel_expression", "simple_expression",
  "term", "unary_expression", "factor", "argument_list", "arguments", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297
};
# endif

#define YYPACT_NINF -73

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-73)))

#define YYTABLE_NINF -21

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      21,   -73,   -73,   -73,    23,    21,   -73,   -73,   -73,   -73,
       8,   -73,   -73,   -18,    20,     5,    27,    16,   -73,    30,
      -5,    35,    24,    44,   -73,    26,    42,    21,   -73,   -73,
      62,    48,   -73,   -73,    26,    45,    51,   103,    54,   -73,
     -73,   -73,    58,    59,    60,    32,   -73,   -73,    32,    32,
      32,   -73,   -11,    61,   -73,   -73,    56,    64,   -73,   -73,
      19,    63,   -73,    67,    22,    76,   -73,   -73,   -73,    32,
      99,    32,    65,    -8,   -73,   -73,    68,    32,    32,    70,
      72,   -73,   -73,   -73,    32,   -73,   -73,    32,    32,    32,
      32,    79,    99,    82,   -73,   -73,   -73,    83,    87,    84,
      94,   -73,   -73,    76,   105,   -73,   103,    32,   103,   -73,
      32,   -73,    91,   127,   101,   -73,   -73,   -73,   103,   103,
     -73,   -73
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    23,    24,    25,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    28,     0,     0,     0,     0,    22,    12,
       0,    17,     0,    26,     9,     0,    10,     0,    16,    29,
       0,    18,    13,     8,     0,    15,     0,     0,     0,    11,
      14,    27,     0,     0,     0,     0,    61,    62,     0,     0,
       0,    41,    43,     0,    34,    32,     0,     0,    30,    33,
      58,     0,    45,    47,    49,    51,    53,    57,    21,     0,
       0,     0,     0,    58,    55,    56,     0,    66,     0,     0,
      28,    19,    31,    63,     0,    64,    42,     0,     0,     0,
       0,     0,     0,     0,    40,    60,    68,     0,    65,     0,
       0,    46,    48,    52,    50,    54,     0,     0,     0,    59,
       0,    44,     0,    36,     0,    38,    67,    39,     0,     0,
      37,    35
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -73,   -73,   -73,   130,   -73,   -73,   -73,   -73,   -73,   -15,
     -73,   -73,    71,     6,   -73,   -73,   -53,   -67,   -48,   -43,
     -72,    53,    49,    57,   -40,   -73,   -73,   -73
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,    34,    25,    20,    54,
      37,    38,    55,    56,    14,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    97,    98
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      73,    73,    72,    92,    82,    96,    10,    76,    74,    75,
      32,    10,   101,    15,     1,     2,    83,    16,     3,    39,
      77,    21,    85,    11,    78,   107,    91,    26,    93,    73,
       1,     2,    27,    35,     3,    99,    73,    19,   116,    73,
      73,    73,    73,    83,    88,    84,    22,    89,    13,    85,
     105,    46,    47,   113,    48,   115,    23,    17,    18,    31,
      29,    49,    73,    50,   114,   120,   121,    42,    24,    43,
      44,     9,    52,     1,     2,    28,     9,     3,    45,    30,
      33,    36,   -20,    46,    47,    40,    48,    41,    68,    69,
      70,    71,    79,    49,    87,    50,    80,    31,    81,    90,
      95,    86,    51,    94,    52,    53,    42,    16,    43,    44,
     100,   106,     1,     2,   108,   109,     3,    45,    46,    47,
     111,    48,    46,    47,   110,    48,   112,    88,    49,   117,
      50,   118,    49,   119,    50,    12,    31,    51,   104,    52,
     102,    51,     0,    52,    53,   103
};

static const yytype_int8 yycheck[] =
{
      48,    49,    45,    70,    57,    77,     0,    50,    48,    49,
      25,     5,    84,    31,     9,    10,    24,    35,    13,    34,
      31,    15,    30,     0,    35,    92,    69,    32,    71,    77,
       9,    10,    37,    27,    13,    78,    84,    32,   110,    87,
      88,    89,    90,    24,    22,    26,    19,    25,    40,    30,
      90,    19,    20,   106,    22,   108,    40,    37,    38,    33,
      36,    29,   110,    31,   107,   118,   119,     3,    38,     5,
       6,     0,    40,     9,    10,    40,     5,    13,    14,    35,
      38,    19,    34,    19,    20,    40,    22,    36,    34,    31,
      31,    31,    31,    29,    27,    31,    40,    33,    34,    23,
      32,    38,    38,    38,    40,    41,     3,    35,     5,     6,
      40,    32,     9,    10,    32,    32,    13,    14,    19,    20,
      36,    22,    19,    20,    37,    22,    32,    22,    29,    38,
      31,     4,    29,    32,    31,     5,    33,    38,    89,    40,
      87,    38,    -1,    40,    41,    88
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    10,    13,    44,    45,    46,    47,    48,    55,
      56,     0,    46,    40,    57,    31,    35,    37,    38,    32,
      51,    56,    19,    40,    38,    50,    32,    37,    40,    36,
      35,    33,    52,    38,    49,    56,    19,    53,    54,    52,
      40,    36,     3,     5,     6,    14,    19,    20,    22,    29,
      31,    38,    40,    41,    52,    55,    56,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    34,    31,
      31,    31,    62,    61,    67,    67,    62,    31,    35,    31,
      40,    34,    59,    24,    26,    30,    38,    27,    22,    25,
      23,    62,    60,    62,    38,    32,    63,    69,    70,    62,
      40,    63,    64,    66,    65,    67,    32,    60,    32,    32,
      37,    36,    32,    59,    62,    59,    63,    38,     4,    32,
      59,    59
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    44,    45,    45,    46,    46,    46,    47,    47,
      49,    48,    50,    48,    51,    51,    51,    51,    53,    52,
      54,    52,    55,    56,    56,    56,    57,    57,    57,    57,
      58,    58,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    60,    60,    61,    61,    62,    62,    63,    63,    64,
      64,    65,    65,    66,    66,    67,    67,    67,    68,    68,
      68,    68,    68,    68,    68,    69,    69,    70,    70
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       0,     7,     0,     6,     4,     3,     2,     1,     0,     4,
       0,     3,     3,     1,     1,     1,     3,     6,     1,     4,
       1,     2,     1,     1,     1,     7,     5,     7,     5,     5,
       3,     1,     2,     1,     4,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     2,     2,     1,     1,     4,
       3,     1,     1,     2,     2,     1,     0,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

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
#line 73 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[0])->getName()  + "\n", "start");
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "start : program\n\n";
		 logfile << (yyval)->getName() <<endl << endl;


		 string finalCode = ".MODEL SMALL\n.STACK 100H\n.DATA \n";

		 for(int i = 0 ; i < variableDeclarationList.size() ; i++) {
			 finalCode += variableDeclarationList[i] + " dw ?\n";
		 }

		 	for(int i=0;i<arrayDeclarationList.size();i++){
		finalCode+=arrayDeclarationList[i].first+" dw "+arrayDeclarationList[i].second+" dup(?)\n";
	}

		
		finalCode += ".CODE\n";
		

		finalCode += (yyvsp[0])->getCode();
		finalCode += outdecProcCode;

		//$1->setCode(finalCode);

  	   asmCodeFile << finalCode;


	//todo Optimization;
	


	 	}
#line 1457 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 110 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-1])->getName() + (yyvsp[0])->getName() + "\n" , "program");
		 (yyval)->addChildSymbol((yyvsp[-1])); (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "program : program unit\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1469 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 117 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[0])->getName() + "\n" , "program");
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "program : unit\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1481 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 126 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[0])->getName() + "\n" , "unit");
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 
		 logfile << "unit : var_declaration\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1494 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 134 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[0])->getName() + "\n" , "unit");
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "unit : func_declaration\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1506 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 141 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[0])->getName() + "\n", "unit");
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "unit : func_definition\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1518 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 150 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-5])->getName() + " " +  (yyvsp[-4])->getName() + " " + (yyvsp[-3])->getName() + (yyvsp[-2])->getName() +
		 (yyvsp[-1])->getName() +
		 (yyvsp[0])->getName() + "\n" , "func_declaration");
		 (yyval)->addChildSymbol((yyvsp[-5])); (yyval)->addChildSymbol((yyvsp[-4])); (yyval)->addChildSymbol((yyvsp[-3])); (yyval)->addChildSymbol((yyvsp[-2]));
		 (yyval)->addChildSymbol((yyvsp[-1]));
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON \n\n";
		 logfile << (yyval)->getName() <<endl << endl;
		
		createSymbolTableEntryForFunctionID((yyvsp[-5]), (yyvsp[-4]), (yyvsp[-2]));

	 	}
#line 1537 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 164 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-4])->getName() + " " + (yyvsp[-3])->getName() + (yyvsp[-2])->getName() + (yyvsp[-1])->getName() +
		 (yyvsp[0])->getName() + "\n" , "func_declaration");
		 (yyval)->addChildSymbol((yyvsp[-4])); (yyval)->addChildSymbol((yyvsp[-3])); (yyval)->addChildSymbol((yyvsp[-2])); (yyval)->addChildSymbol((yyvsp[-1]));
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON	\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
		createSymbolTableEntryForFunctionID((yyvsp[-4]), (yyvsp[-3]));

	 	}
#line 1553 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 178 "1605115_parser.y" /* yacc.c:1646  */
    {
	string functionName = (yyvsp[-3])->getName();
	SymbolInfo* generateEntry = createSymbolInfoForFunctionID((yyvsp[-4]), (yyvsp[-3]), (yyvsp[-1]));

	SymbolInfo *tableEntry = symbolTable.lookup(functionName);
	if (tableEntry == nullptr) { //function did not have a declaration. So do it now.
	   insertIDToSymbolTable(generateEntry);
		symbolTable.printAllScopeTable(scratchfile);

	} else {
		if (!checkFunctionSymbolInfoEquality(generateEntry, tableEntry)) {
			addLineNoErr();
			logfile << "Function declaration does not match function definition\n\n";
		};
	}


	symbolTable.enterScope();

	functionScopeBeginFlag = true;
	
	

	for (int i = 0; i < generateEntry->getFunctionInfoDataPtr()->getArgumentsNumber(); i++) {
		ArgumentInfo arg = generateEntry->getFunctionInfoDataPtr()->getArguments()[i];
		SymbolInfo* argIDEntry = new SymbolInfo(arg.getArgumentName(), "ID");
		argIDEntry->initializeVariable(arg.getArgumentName());
		insertIDToSymbolTable(argIDEntry);
		
	}

	//todo -> Add arguments to the new scope in symboltable

  }
#line 1592 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 211 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-6])->getName() + " " + (yyvsp[-5])->getName() + (yyvsp[-4])->getName() + (yyvsp[-3])->getName() +
		 (yyvsp[-2])->getName() + "\n" +  (yyvsp[0])->getName(), "func_definition");
		 (yyval)->addChildSymbol((yyvsp[-6])); (yyval)->addChildSymbol((yyvsp[-5])); (yyval)->addChildSymbol((yyvsp[-4])); (yyval)->addChildSymbol((yyvsp[-3]));
		 (yyval)->addChildSymbol((yyvsp[-2]));
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1607 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 221 "1605115_parser.y" /* yacc.c:1646  */
    {
	
	string functionName = (yyvsp[-2])->getName();
	SymbolInfo *tableEntry = symbolTable.lookup(functionName);
	if (tableEntry == nullptr) { //function did not have a declaration. So do it now.
	createSymbolTableEntryForFunctionID((yyvsp[-3]), (yyvsp[-2]));

	} else {
		SymbolInfo* generateEntry = createSymbolInfoForFunctionID((yyvsp[-3]), (yyvsp[-2]));
		if (!checkFunctionSymbolInfoEquality(generateEntry, tableEntry)) {
			addLineNoErr();
			logfile << "Function declaration does not match function definition\n\n";
		};
	}

	symbolTable.enterScope();

	functionScopeBeginFlag = true;
	
  }
#line 1632 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 240 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-5])->getName() + " " +  (yyvsp[-4])->getName() + (yyvsp[-3])->getName() + (yyvsp[-2])->getName() + "\n " + 
		 (yyvsp[0])->getName(), "func_definition");
		 (yyval)->addChildSymbol((yyvsp[-5])); (yyval)->addChildSymbol((yyvsp[-4])); (yyval)->addChildSymbol((yyvsp[-3])); (yyval)->addChildSymbol((yyvsp[-2]));
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "func_definition : type_specifier ID LPAREN RPAREN compound_statement\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1646 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 252 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-3])->getName() + (yyvsp[-2])->getName() + " " + (yyvsp[-1])->getName() + " " + (yyvsp[0])->getName(), "parameter_list");
		 (yyval)->addChildSymbol((yyvsp[-3])); (yyval)->addChildSymbol((yyvsp[-2])); (yyval)->addChildSymbol((yyvsp[-1])); (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "parameter_list : parameter_list COMMA type_specifier ID\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1658 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 259 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-2])->getName() + (yyvsp[-1])->getName() + " " + (yyvsp[0])->getName(), "parameter_list");
		 (yyval)->addChildSymbol((yyvsp[-2])); (yyval)->addChildSymbol((yyvsp[-1])); (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "parameter_list : parameter_list COMMA type_specifier\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1670 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 266 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-1])->getName() + " " + (yyvsp[0])->getName() , "parameter_list");
		 (yyval)->addChildSymbol((yyvsp[-1])); (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "parameter_list : type_specifier ID\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1682 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 273 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[0])->getName()  + " " , "parameter_list");
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "parameter_list : type_specifier\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1694 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 283 "1605115_parser.y" /* yacc.c:1646  */
    {
	if(functionScopeBeginFlag) {
		functionScopeBeginFlag = false;
	} else {
		symbolTable.enterScope();
	}
}
#line 1706 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 289 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-3])->getName() + (yyvsp[-1])->getName() + (yyvsp[0])->getName(), "compound_statement");
		 (yyval)->addChildSymbol((yyvsp[-3])); (yyval)->addChildSymbol((yyvsp[-1])); (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "compound_statement : LCURL statements RCURL\n\n";
		 logfile << (yyval)->getName() <<endl << endl;

		 symbolTable.printAllScopeTable(logfile);
		 symbolTable.exitScope();
	 	}
#line 1721 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 299 "1605115_parser.y" /* yacc.c:1646  */
    { 
			if(functionScopeBeginFlag) {
				functionScopeBeginFlag = false;
			} else {
				symbolTable.enterScope();
			}		 	
		 }
#line 1733 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 305 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-2])->getName() + (yyvsp[0])->getName() , "compound_statement");
		 (yyval)->addChildSymbol((yyvsp[-2])); (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "compound_statement : LCURL RCURL\n\n";
		 logfile << (yyval)->getName() <<endl << endl;

		 symbolTable.printAllScopeTable(logfile);
		 symbolTable.exitScope();
	 	}
#line 1748 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 317 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-2])->getName() + " " + (yyvsp[-1])->getName() + (yyvsp[0])->getName() + "\n" , "var_declaration");
		 (yyval)->addChildSymbol((yyvsp[-2])); (yyval)->addChildSymbol((yyvsp[-1])); (yyval)->addChildSymbol((yyvsp[0]));

		 
		 addLineNoLog();
		 logfile << "var_declaration : type_specifier declaration_list SEMICOLON\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
		
		 symbolTableEntryForVarDeclaration((yyvsp[-2]), (yyvsp[-1]));
	 	}
#line 1764 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 330 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[0])->getName() , "type_specifier");
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "type_specifier : INT\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1776 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 337 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[0])->getName() , "type_specifier");
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "type_specifier : FLOAT\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1788 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 344 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[0])->getName() , "type_specifier");
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "type_specifier : VOID\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1800 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 354 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-2])->getName() + (yyvsp[-1])->getName() + " " +  (yyvsp[0])->getName(), "declaration_list");
		 (yyval)->addChildSymbol((yyvsp[-2])); (yyval)->addChildSymbol((yyvsp[-1])); (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "declaration_list : declaration_list COMMA ID\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1812 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 361 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-5])->getName() + (yyvsp[-4])->getName() + " " +  (yyvsp[-3])->getName() + (yyvsp[-2])->getName() +
		 (yyvsp[-1])->getName() +
		 (yyvsp[0])->getName(), "declaration_list");
		 (yyval)->addChildSymbol((yyvsp[-5])); (yyval)->addChildSymbol((yyvsp[-4])); (yyval)->addChildSymbol((yyvsp[-3])); (yyval)->addChildSymbol((yyvsp[-2]));
		 (yyval)->addChildSymbol((yyvsp[-1]));
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1828 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 372 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[0])->getName() , "declaration_list");
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "declaration_list : ID\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1840 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 379 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-3])->getName() + (yyvsp[-2])->getName() + (yyvsp[-1])->getName() + (yyvsp[0])->getName(), "declaration_list");
		 (yyval)->addChildSymbol((yyvsp[-3])); (yyval)->addChildSymbol((yyvsp[-2])); (yyval)->addChildSymbol((yyvsp[-1])); (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "declaration_list : ID LTHIRD CONST_INT RTHIRD\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1852 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 388 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[0])->getName() , "statements");
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "statements : statement\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1864 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 395 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-1])->getName() + (yyvsp[0])->getName() , "statements");
		 (yyval)->addChildSymbol((yyvsp[-1])); (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "statements : statements statement\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1876 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 404 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[0])->getName() , "statement");
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "statement : var_declaration\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1888 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 411 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[0])->getName() , "statement");
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "statement : expression_statement\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1900 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 418 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[0])->getName() , "statement");
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "statement : compound_statement\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1912 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 425 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-6])->getName() + (yyvsp[-5])->getName() + (yyvsp[-4])->getName() + (yyvsp[-3])->getName() +
		 (yyvsp[-2])->getName() + (yyvsp[-1])->getName() + (yyvsp[0])->getName(), "statement");
		 (yyval)->addChildSymbol((yyvsp[-6])); (yyval)->addChildSymbol((yyvsp[-5])); (yyval)->addChildSymbol((yyvsp[-4])); (yyval)->addChildSymbol((yyvsp[-3]));
		 (yyval)->addChildSymbol((yyvsp[-2]));
		 (yyval)->addChildSymbol((yyvsp[-1]));
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1928 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 436 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-4])->getName() + (yyvsp[-3])->getName() + (yyvsp[-2])->getName() + (yyvsp[-1])->getName() +
		 (yyvsp[0])->getName(), "statement");
		 (yyval)->addChildSymbol((yyvsp[-4])); (yyval)->addChildSymbol((yyvsp[-3])); (yyval)->addChildSymbol((yyvsp[-2])); (yyval)->addChildSymbol((yyvsp[-1]));
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "statement : IF LPAREN expression RPAREN statement\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1942 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 445 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-6])->getName() + (yyvsp[-5])->getName() + (yyvsp[-4])->getName() + (yyvsp[-3])->getName() +
		 (yyvsp[-2])->getName() + (yyvsp[-1])->getName() + (yyvsp[0])->getName(), "statement");
		 (yyval)->addChildSymbol((yyvsp[-6])); (yyval)->addChildSymbol((yyvsp[-5])); (yyval)->addChildSymbol((yyvsp[-4])); (yyval)->addChildSymbol((yyvsp[-3]));
		 (yyval)->addChildSymbol((yyvsp[-2]));
		 (yyval)->addChildSymbol((yyvsp[-1]));
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "statement : IF LPAREN expression RPAREN statement ELSE statement\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1958 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 456 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-4])->getName() + (yyvsp[-3])->getName() + (yyvsp[-2])->getName() + (yyvsp[-1])->getName() +
		 (yyvsp[0])->getName(), "statement");
		 (yyval)->addChildSymbol((yyvsp[-4])); (yyval)->addChildSymbol((yyvsp[-3])); (yyval)->addChildSymbol((yyvsp[-2])); (yyval)->addChildSymbol((yyvsp[-1]));
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "statement : WHILE LPAREN expression RPAREN statement\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1972 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 465 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-4])->getName() + (yyvsp[-3])->getName() + (yyvsp[-2])->getName() + (yyvsp[-1])->getName() +
		 (yyvsp[0])->getName(), "statement");
		 (yyval)->addChildSymbol((yyvsp[-4])); (yyval)->addChildSymbol((yyvsp[-3])); (yyval)->addChildSymbol((yyvsp[-2])); (yyval)->addChildSymbol((yyvsp[-1]));
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1986 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 474 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-2])->getName() + " " + (yyvsp[-1])->getName() + (yyvsp[0])->getName(), "statement");
		 (yyval)->addChildSymbol((yyvsp[-2])); (yyval)->addChildSymbol((yyvsp[-1])); (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "statement : RETURN expression SEMICOLON\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 1998 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 483 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[0])->getName()  + "\n" , "expression_statement");
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "expression_statement : SEMICOLON\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 2010 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 490 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-1])->getName() + (yyvsp[0])->getName() + "\n"  , "expression_statement");
		 (yyval)->addChildSymbol((yyvsp[-1])); (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "expression_statement : expression SEMICOLON\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 2022 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 499 "1605115_parser.y" /* yacc.c:1646  */
    {
				(yyval) = new SymbolInfo((yyvsp[0])->getName(), "variable");

				(yyval)->addChildSymbol((yyvsp[0]));
				addLineNoLog();
				 logfile << "variable : ID" << endl << endl;
				 logfile << (yyvsp[0])->getName() << endl << endl;

				verifyVariableIDIsDeclared((yyvsp[0]));
				(yyval)->setReturnType(getReturnTypeOfSymbolTableEntry((yyvsp[0])->getName()));	

				(yyval)->setCode("");




		}
#line 2044 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 516 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-3])->getName() + (yyvsp[-2])->getName() + (yyvsp[-1])->getName() + (yyvsp[0])->getName(), "variable");
		 (yyval)->addChildSymbol((yyvsp[-3])); (yyval)->addChildSymbol((yyvsp[-2])); (yyval)->addChildSymbol((yyvsp[-1])); (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "variable : ID LTHIRD expression RTHIRD\n\n";
		 logfile << (yyval)->getName() <<endl << endl;

		verifyArrayIDIsDeclared((yyvsp[-3]));
		if( (yyvsp[-1])->getReturnType() != "int"){
			addLineNoErr();
			logfile << "Non Integer Array index\n\n";
		}
		(yyval)->setReturnType(getReturnTypeOfSymbolTableEntry((yyvsp[-3])->getName()));		

		string codes = "";
		codes += (yyvsp[-1])->getCode();
		codes += "\tMOV BX," + (yyvsp[-1])->getAssemblyID() + "\n";
		codes+="\tADD BX,BX\n";  //todo find out why tf we're doing this
		(yyval)->setAssemblyArrayMember(true);


		//instead of generating it manually based on symbol table data like bhaia did, we just fetch the assemblyName assigned to ID in symboltable.
		//ID was given a assemblyName during declaration.
		string assemblyName = symbolTable.lookup((yyvsp[-3])->getName())->getAssemblyID();


		(yyval)->setCode(codes);
		(yyval)->setAssemblyID(assemblyName);

		scratchfile << "variable with code created. CODE: \n" << codes;

	 }
#line 2081 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 550 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[0])->getName() , "expression");
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "expression : logic_expression\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
		 (yyval)->setReturnType((yyvsp[0])->getReturnType());

		//  if($$->getReturnType() == "" || $$->getReturnType() == "void") {
		// 	cerr<< ($$->getName() << "Expression with return type: " << $$->getReturnType() << " - in line " << line_no << endl << endl;
		//  }

		(yyval)->setReturnType((yyvsp[0])->getReturnType());
	 	}
#line 2100 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 564 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-2])->getName() + " " +  (yyvsp[-1])->getName() + " " + (yyvsp[0])->getName(), "expression");
		 (yyval)->addChildSymbol((yyvsp[-2])); (yyval)->addChildSymbol((yyvsp[-1])); (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "expression : variable ASSIGNOP logic_expression\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
		evaluateTypeConversionForASSIGNOP((yyvsp[-2]), (yyvsp[0]));
		 (yyval)->setReturnType((yyvsp[-2])->getReturnType());

	 	}
#line 2115 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 576 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[0])->getName() , "logic_expression");
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "logic_expression : rel_expression\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
		 (yyval)->setReturnType((yyvsp[0])->getReturnType());	
		  	}
#line 2128 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 584 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-2])->getName() + " " + (yyvsp[-1])->getName() + " " +  (yyvsp[0])->getName(), "logic_expression");
		 (yyval)->addChildSymbol((yyvsp[-2])); (yyval)->addChildSymbol((yyvsp[-1])); (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "logic_expression : rel_expression LOGICOP rel_expression\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
		 (yyval)->setReturnType("int");

	 	}
#line 2142 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 595 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[0])->getName() , "rel_expression");
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "rel_expression : simple_expression\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
		 (yyval)->setReturnType((yyvsp[0])->getReturnType());
	 	}
#line 2155 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 603 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-2])->getName() + " " + (yyvsp[-1])->getName() + " " +  (yyvsp[0])->getName(), "rel_expression");
		 (yyval)->addChildSymbol((yyvsp[-2])); (yyval)->addChildSymbol((yyvsp[-1])); (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "rel_expression : simple_expression RELOP simple_expression\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
		 (yyval)->setReturnType("int");
	 	}
#line 2168 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 613 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[0])->getName() , "simple_expression");
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "simple_expression : term\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
		 (yyval)->setReturnType((yyvsp[0])->getReturnType());
	 	}
#line 2181 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 621 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-2])->getName() + " " +  (yyvsp[-1])->getName() + " " +  (yyvsp[0])->getName(), "simple_expression");
		 (yyval)->addChildSymbol((yyvsp[-2])); (yyval)->addChildSymbol((yyvsp[-1])); (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "simple_expression : simple_expression ADDOP term\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
		 (yyval)->setReturnType(evaluateReturnTypeForADDOP((yyvsp[-2]),(yyvsp[0])));
	 	}
#line 2194 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 631 "1605115_parser.y" /* yacc.c:1646  */
    {
						(yyval) = new SymbolInfo((yyvsp[0])->getName(), "term");
						(yyval)->addChildSymbol((yyvsp[0]));
						addLineNoLog();
						logfile << "term : unary_expression\n\n";
						logfile << (yyval)->getName() << endl << endl;
						(yyval)->setReturnType((yyvsp[0])->getReturnType());
	}
#line 2207 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 639 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-2])->getName() + " " +   (yyvsp[-1])->getName() + " " + (yyvsp[0])->getName(), "term");
		 (yyval)->addChildSymbol((yyvsp[-2])); (yyval)->addChildSymbol((yyvsp[-1])); (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "term : term MULOP unary_expression\n\n";
		 logfile << (yyval)->getName() <<endl << endl;

		 (yyval)->setReturnType(evaluateReturnTypeForMULOP((yyvsp[-2]), (yyvsp[-1]), (yyvsp[0])));

	}
#line 2222 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 651 "1605115_parser.y" /* yacc.c:1646  */
    {
						(yyval) = new SymbolInfo((yyvsp[-1])->getName() + " " +  (yyvsp[0])->getName(), "unary_expression");
						(yyval)->addChildSymbol((yyvsp[-1])); (yyval)->addChildSymbol((yyvsp[0]));
						addLineNoLog();
						logfile << "unary_expression : ADDOP unary_expression\n\n";
						logfile << (yyval)->getName() << endl << endl;
						if( checkIfValidFunctionReturnTypeInExpression((yyvsp[0])) ) {
							string retType = (yyvsp[0])->getReturnType();
							(yyval)->setReturnType(retType);

							string code = (yyvsp[0])->getCode();

							if((yyvsp[-1])->getName() == "-") {
								code+="MOV AX,"+(yyvsp[0])->getAssemblyID()+"\n";
								code+="NEG AX\n";
								code+="MOV "+(yyvsp[0])->getAssemblyID()+",AX\n";
							} 

							(yyval)->setCode(code);
							(yyval)->setAssemblyID((yyvsp[0])->getAssemblyID());

						} else {
						(yyval)->setReturnType("invalid");		
						//todo verify if setting this to invalid is the right thing.
						//we've already given an error if the return type is invalid. 
						//so this is going to propogate the error further up the gramar.
						}
					

	}
#line 2257 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 681 "1605115_parser.y" /* yacc.c:1646  */
    {
						(yyval) = new SymbolInfo((yyvsp[-1])->getName() + (yyvsp[0])->getName(), "unary_expression");
						(yyval)->addChildSymbol((yyvsp[-1])); (yyval)->addChildSymbol((yyvsp[0]));
						addLineNoLog();
						logfile << "unary_expression : NOT unary_expression\n\n";
						logfile << (yyval)->getName() << endl << endl;
						checkIfValidFunctionReturnTypeInExpression((yyvsp[0]));
						(yyval)->setReturnType("int");
						
						string code = (yyvsp[0])->getCode();
						code+="MOV AX,"+(yyvsp[0])->getAssemblyID()+"\n";
						code+="NOT AX\n";
						code+="MOV "+(yyvsp[0])->getAssemblyID()+",AX\n";

						(yyval)->setCode(code);
						(yyval)->setAssemblyID((yyvsp[0])->getAssemblyID());
						

	}
#line 2281 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 700 "1605115_parser.y" /* yacc.c:1646  */
    {
						(yyval) = new SymbolInfo((yyvsp[0])->getName(), "unary_expression");
						(yyval)->addChildSymbol((yyvsp[0]));
						addLineNoLog();
						logfile << "unary_expression : factor\n\n";
						logfile << (yyval)->getName() << endl << endl;
						(yyval)->setReturnType((yyvsp[0])->getReturnType());
						(yyval)->setCode((yyvsp[0])->getCode());
						(yyval)->setAssemblyID((yyvsp[0])->getAssemblyID());

	}
#line 2297 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 713 "1605115_parser.y" /* yacc.c:1646  */
    {
						(yyval) = new SymbolInfo((yyvsp[0])->getName(), "factor");
						(yyval)->addChildSymbol((yyvsp[0]));

						addLineNoLog();
						logfile << "factor : variable\n\n";
						logfile << (yyval)->getName() << endl << endl;
						(yyval)->setReturnType((yyvsp[0])->getReturnType());
						string currentCode = (yyvsp[0])->getCode();
						if((yyvsp[0])->isAssemblyArrayMember()) {
							string tempVar = generateNewTempVariable();
							currentCode += "MOV AX, " + (yyvsp[0])->getAssemblyID() + "[BX]\n";
							currentCode += "MOV " + tempVar + ",AX\n";
							(yyval)->setAssemblyID(tempVar);
						} else {
							(yyval)->setAssemblyID((yyvsp[0])->getAssemblyID());
						}

						(yyval)->setCode(currentCode);
						
	}
#line 2323 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 734 "1605115_parser.y" /* yacc.c:1646  */
    {
		//todo Function call. Handle Later.

		 (yyval) = new SymbolInfo((yyvsp[-3])->getName() + (yyvsp[-2])->getName() + (yyvsp[-1])->getName() + (yyvsp[0])->getName(), "factor");
		 (yyval)->addChildSymbol((yyvsp[-3])); (yyval)->addChildSymbol((yyvsp[-2])); (yyval)->addChildSymbol((yyvsp[-1])); (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "factor : ID LPAREN argument_list RPAREN\n\n";
		 logfile << (yyval)->getName() <<endl << endl;

		 //todo Evaluate function called with appropriate number of variables etc etc
		functionCallValidationWithArgumentTypeCheck((yyvsp[-3]), (yyvsp[-1]));
		 (yyval)->setReturnType(getReturnTypeOfSymbolTableEntry((yyvsp[-3])->getName()));		 

		 
	}
#line 2343 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 749 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-2])->getName() + (yyvsp[-1])->getName() + (yyvsp[0])->getName(), "factor");
		 (yyval)->addChildSymbol((yyvsp[-2])); (yyval)->addChildSymbol((yyvsp[-1])); (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "factor : LPAREN expression RPAREN\n\n";
		 logfile << (yyval)->getName() <<endl << endl;

		 (yyval)->setReturnType((yyvsp[-1])->getReturnType());
		 (yyval)->setCode((yyvsp[-1])->getCode());
		 (yyval)->setAssemblyID((yyvsp[-1])->getAssemblyID());
	}
#line 2359 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 760 "1605115_parser.y" /* yacc.c:1646  */
    {
			(yyval) = new SymbolInfo((yyvsp[0])->getName(), "factor");
			(yyval)->addChildSymbol((yyvsp[0]));
			addLineNoLog();
			logfile << "factor : CONST_INT\n\n";
			logfile << (yyval)->getName() << endl << endl;
			(yyval)->setReturnType("int");

			string temp = generateNewTempVariable();
			string code = "\tMOV " + temp + "," + (yyvsp[0])->getName() + "\n";
			(yyval)->setAssemblyID(temp);
			(yyval)->setCode(code);

	 }
#line 2378 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 774 "1605115_parser.y" /* yacc.c:1646  */
    {
			(yyval) = new SymbolInfo((yyvsp[0])->getName(), "factor");
			(yyval)->addChildSymbol((yyvsp[0]));
			addLineNoLog();
			logfile << "factor : CONST_FLOAT\n\n";
			logfile << (yyval)->getName() << endl << endl;
			(yyval)->setReturnType("float");

			string temp = generateNewTempVariable();
			string code = "\tMOV " + temp + "," + (yyvsp[0])->getName() + "\n";
			(yyval)->setAssemblyID(temp);
			(yyval)->setCode(code);
	 }
#line 2396 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 787 "1605115_parser.y" /* yacc.c:1646  */
    {
			(yyval) = new SymbolInfo((yyvsp[-1])->getName() + (yyvsp[0])->getName(), "factor");
			(yyval)->addChildSymbol((yyvsp[-1])); (yyval)->addChildSymbol((yyvsp[0]));
			addLineNoLog();
			logfile << "factor : variable INCOP\n\n";
			logfile << (yyval)->getName() << endl << endl;

			(yyval)->setReturnType((yyvsp[-1])->getReturnType());

			string tempVar = generateNewTempVariable();
			string codes = "";


			if((yyval)->isAssemblyArrayMember()) {
				codes+="MOV AX,"+(yyvsp[-1])->getAssemblyID()+"[BX]\n";	
				codes+="MOV "+ tempVar +",AX\n";
				codes+="MOV AX,"+(yyvsp[-1])->getAssemblyID()+"[BX]\n";
				codes+="INC AX\n";
				codes+="MOV "+(yyvsp[-1])->getAssemblyID()+"[BX],AX\n";


			} else {
			codes+="MOV AX,"+(yyvsp[-1])->getAssemblyID()+"\n";	
			codes+="MOV "+ tempVar +",AX\n";
			codes+="INC "+(yyvsp[-1])->getAssemblyID()+"\n";

			}


			(yyval)->setCode(codes);
			(yyval)->setAssemblyID(tempVar);



			
	}
#line 2437 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 823 "1605115_parser.y" /* yacc.c:1646  */
    {
			(yyval) = new SymbolInfo((yyvsp[-1])->getName() + (yyvsp[0])->getName(), "factor");
			(yyval)->addChildSymbol((yyvsp[-1])); (yyval)->addChildSymbol((yyvsp[0]));
			addLineNoLog();
			logfile << "factor : variable DECOP\n\n";
			logfile << (yyval)->getName() << endl << endl;

			(yyval)->setReturnType((yyvsp[-1])->getReturnType());

			string tempVar = generateNewTempVariable();
			string codes = "";


			if((yyval)->isAssemblyArrayMember()) {
				codes+="MOV AX,"+(yyvsp[-1])->getAssemblyID()+"[BX]\n";	
				codes+="MOV "+ tempVar +",AX\n";
				codes+="MOV AX,"+(yyvsp[-1])->getAssemblyID()+"[BX]\n";
				codes+="DEC AX\n";
				codes+="MOV "+(yyvsp[-1])->getAssemblyID()+"[BX],AX\n";


			} else {
			codes+="MOV AX,"+(yyvsp[-1])->getAssemblyID()+"\n";	
			codes+="MOV "+ tempVar +",AX\n";
			codes+="DEC "+(yyvsp[-1])->getAssemblyID()+"\n";

			}


			(yyval)->setCode(codes);
			(yyval)->setAssemblyID(tempVar);
	}
#line 2474 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 857 "1605115_parser.y" /* yacc.c:1646  */
    { 
		 (yyval) = new SymbolInfo((yyvsp[0])->getName() , "argument_list");
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "argument_list : arguments\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 2486 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 864 "1605115_parser.y" /* yacc.c:1646  */
    {
				  (yyval) = new SymbolInfo("", "argument_list");
		 		 
				 addLineNoLog();
		 		logfile << "argument_list : \n\n";
		 		logfile << (yyval)->getName() <<endl << endl;
			  }
#line 2498 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 873 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[-2])->getName() + (yyvsp[-1])->getName() + (yyvsp[0])->getName(), "arguments");
		 (yyval)->addChildSymbol((yyvsp[-2])); (yyval)->addChildSymbol((yyvsp[-1])); (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "arguments : arguments COMMA logic_expression\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 2510 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 880 "1605115_parser.y" /* yacc.c:1646  */
    {
		 (yyval) = new SymbolInfo((yyvsp[0])->getName() , "arguments");
		 (yyval)->addChildSymbol((yyvsp[0]));
		 addLineNoLog();
		 logfile << "arguments : logic_expression\n\n";
		 logfile << (yyval)->getName() <<endl << endl;
	 	}
#line 2522 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2526 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 890 "1605115_parser.y" /* yacc.c:1906  */

int main(int argc,char *argv[])
{

	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	   logfile.open("1605115_log.txt");
	   scratchfile.open("scratch.txt");
	   asmCodeFile.open("outputCode.asm");

		


	yyin=fp;
	yyparse();


	symbolTable.printAllScopeTable(logfile);


	logfile << "Total Lines: " << line_no << endl;
	logfile << "Total Errors: " << errorCount << endl;
	logfile << "Total Errors: " << errorCount << endl;


	logfile.close();
	scratchfile.close();
	asmCodeFile.close();


	return 0;
}
