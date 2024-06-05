/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "til_parser.y"

//-- don't change *any* of these: if you do, you'll break the compiler.
#include <algorithm>
#include <memory>
#include <cstring>
#include <cdk/compiler.h>
#include <cdk/types/types.h>
#include ".auto/all_nodes.h"
#define LINE                         compiler->scanner()->lineno()
#define yylex()                      compiler->scanner()->scan()
#define yyerror(compiler, s)         compiler->scanner()->error(s)
//-- don't change *any* of these --- END!

#line 85 "til_parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "til_parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_tINTEGER = 3,                   /* tINTEGER  */
  YYSYMBOL_tDOUBLE = 4,                    /* tDOUBLE  */
  YYSYMBOL_tIDENTIFIER = 5,                /* tIDENTIFIER  */
  YYSYMBOL_tSTRING = 6,                    /* tSTRING  */
  YYSYMBOL_tLOOP = 7,                      /* tLOOP  */
  YYSYMBOL_tIF = 8,                        /* tIF  */
  YYSYMBOL_tPRINT = 9,                     /* tPRINT  */
  YYSYMBOL_tREAD = 10,                     /* tREAD  */
  YYSYMBOL_tPROGRAM = 11,                  /* tPROGRAM  */
  YYSYMBOL_tSET = 12,                      /* tSET  */
  YYSYMBOL_tTYPE_INT = 13,                 /* tTYPE_INT  */
  YYSYMBOL_tYPE_DOUBLE = 14,               /* tYPE_DOUBLE  */
  YYSYMBOL_tTYPE_STRING = 15,              /* tTYPE_STRING  */
  YYSYMBOL_tAT = 16,                       /* tAT  */
  YYSYMBOL_tTYPE_VOID = 17,                /* tTYPE_VOID  */
  YYSYMBOL_tEXTERNAL = 18,                 /* tEXTERNAL  */
  YYSYMBOL_tTYPE_DOUBLE = 19,              /* tTYPE_DOUBLE  */
  YYSYMBOL_tNULLPTR = 20,                  /* tNULLPTR  */
  YYSYMBOL_tFORWARD = 21,                  /* tFORWARD  */
  YYSYMBOL_tPUBLIC = 22,                   /* tPUBLIC  */
  YYSYMBOL_tVAR = 23,                      /* tVAR  */
  YYSYMBOL_tBLOCK = 24,                    /* tBLOCK  */
  YYSYMBOL_tSTOP = 25,                     /* tSTOP  */
  YYSYMBOL_tWITH = 26,                     /* tWITH  */
  YYSYMBOL_tNEXT = 27,                     /* tNEXT  */
  YYSYMBOL_tRETURN = 28,                   /* tRETURN  */
  YYSYMBOL_tPRINTLN = 29,                  /* tPRINTLN  */
  YYSYMBOL_tAND = 30,                      /* tAND  */
  YYSYMBOL_tOR = 31,                       /* tOR  */
  YYSYMBOL_tFIND = 32,                     /* tFIND  */
  YYSYMBOL_tINDEX = 33,                    /* tINDEX  */
  YYSYMBOL_tOBJECTS = 34,                  /* tOBJECTS  */
  YYSYMBOL_tSIZEOF = 35,                   /* tSIZEOF  */
  YYSYMBOL_tFUNCTION = 36,                 /* tFUNCTION  */
  YYSYMBOL_tPRIVATE = 37,                  /* tPRIVATE  */
  YYSYMBOL_tUNLESS = 38,                   /* tUNLESS  */
  YYSYMBOL_tDO = 39,                       /* tDO  */
  YYSYMBOL_tFOR = 40,                      /* tFOR  */
  YYSYMBOL_tAPPLY = 41,                    /* tAPPLY  */
  YYSYMBOL_tDOTS = 42,                     /* tDOTS  */
  YYSYMBOL_tARROW = 43,                    /* tARROW  */
  YYSYMBOL_tSWEEP = 44,                    /* tSWEEP  */
  YYSYMBOL_tCHANGE = 45,                   /* tCHANGE  */
  YYSYMBOL_tIFX = 46,                      /* tIFX  */
  YYSYMBOL_tELSE = 47,                     /* tELSE  */
  YYSYMBOL_tGE = 48,                       /* tGE  */
  YYSYMBOL_tLE = 49,                       /* tLE  */
  YYSYMBOL_tEQ = 50,                       /* tEQ  */
  YYSYMBOL_tNE = 51,                       /* tNE  */
  YYSYMBOL_52_ = 52,                       /* '>'  */
  YYSYMBOL_53_ = 53,                       /* '<'  */
  YYSYMBOL_54_ = 54,                       /* '+'  */
  YYSYMBOL_55_ = 55,                       /* '-'  */
  YYSYMBOL_56_ = 56,                       /* '*'  */
  YYSYMBOL_57_ = 57,                       /* '/'  */
  YYSYMBOL_58_ = 58,                       /* '%'  */
  YYSYMBOL_59_ = 59,                       /* '('  */
  YYSYMBOL_60_ = 60,                       /* ')'  */
  YYSYMBOL_61_ = 61,                       /* '~'  */
  YYSYMBOL_62_ = 62,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 63,                  /* $accept  */
  YYSYMBOL_file = 64,                      /* file  */
  YYSYMBOL_main = 65,                      /* main  */
  YYSYMBOL_global_declarations = 66,       /* global_declarations  */
  YYSYMBOL_global_declaration = 67,        /* global_declaration  */
  YYSYMBOL_opt_global_init = 68,           /* opt_global_init  */
  YYSYMBOL_global_init = 69,               /* global_init  */
  YYSYMBOL_opt_init = 70,                  /* opt_init  */
  YYSYMBOL_var = 71,                       /* var  */
  YYSYMBOL_block = 72,                     /* block  */
  YYSYMBOL_block_content = 73,             /* block_content  */
  YYSYMBOL_declarations = 74,              /* declarations  */
  YYSYMBOL_declaration = 75,               /* declaration  */
  YYSYMBOL_instrs = 76,                    /* instrs  */
  YYSYMBOL_instr = 77,                     /* instr  */
  YYSYMBOL_opt_exprs = 78,                 /* opt_exprs  */
  YYSYMBOL_exprs = 79,                     /* exprs  */
  YYSYMBOL_expr = 80,                      /* expr  */
  YYSYMBOL_fundef = 81,                    /* fundef  */
  YYSYMBOL_data_type = 82,                 /* data_type  */
  YYSYMBOL_fun_type = 83,                  /* fun_type  */
  YYSYMBOL_return_type = 84,               /* return_type  */
  YYSYMBOL_opt_args = 85,                  /* opt_args  */
  YYSYMBOL_args = 86,                      /* args  */
  YYSYMBOL_arg = 87,                       /* arg  */
  YYSYMBOL_var_types = 88,                 /* var_types  */
  YYSYMBOL_var_type = 89,                  /* var_type  */
  YYSYMBOL_void_pointer = 90,              /* void_pointer  */
  YYSYMBOL_void_type = 91,                 /* void_type  */
  YYSYMBOL_literal = 92,                   /* literal  */
  YYSYMBOL_lval = 93                       /* lval  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 67 "til_parser.y"

//-- The rules below will be included in yyparse, the main parsing function.

#line 216 "til_parser.tab.c"


#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  23
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   488

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  109
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  266

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   306


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    62,     2,     2,     2,    58,     2,     2,
      59,    60,    56,    54,     2,    55,     2,    57,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      53,     2,    52,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    61,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    72,    72,    73,    74,    75,    78,    81,    82,    85,
      86,    87,    88,    89,    90,    91,    92,    95,    96,    99,
     100,   103,   104,   107,   110,   113,   114,   115,   116,   119,
     120,   123,   124,   127,   128,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   150,   151,   154,   155,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   186,   191,   192,   193,   194,   195,   198,   199,
     202,   203,   206,   207,   210,   211,   214,   217,   218,   221,
     222,   225,   226,   229,   232,   233,   234,   235,   238,   239
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "tINTEGER", "tDOUBLE",
  "tIDENTIFIER", "tSTRING", "tLOOP", "tIF", "tPRINT", "tREAD", "tPROGRAM",
  "tSET", "tTYPE_INT", "tYPE_DOUBLE", "tTYPE_STRING", "tAT", "tTYPE_VOID",
  "tEXTERNAL", "tTYPE_DOUBLE", "tNULLPTR", "tFORWARD", "tPUBLIC", "tVAR",
  "tBLOCK", "tSTOP", "tWITH", "tNEXT", "tRETURN", "tPRINTLN", "tAND",
  "tOR", "tFIND", "tINDEX", "tOBJECTS", "tSIZEOF", "tFUNCTION", "tPRIVATE",
  "tUNLESS", "tDO", "tFOR", "tAPPLY", "tDOTS", "tARROW", "tSWEEP",
  "tCHANGE", "tIFX", "tELSE", "tGE", "tLE", "tEQ", "tNE", "'>'", "'<'",
  "'+'", "'-'", "'*'", "'/'", "'%'", "'('", "')'", "'~'", "'!'", "$accept",
  "file", "main", "global_declarations", "global_declaration",
  "opt_global_init", "global_init", "opt_init", "var", "block",
  "block_content", "declarations", "declaration", "instrs", "instr",
  "opt_exprs", "exprs", "expr", "fundef", "data_type", "fun_type",
  "return_type", "opt_args", "args", "arg", "var_types", "var_type",
  "void_pointer", "void_type", "literal", "lval", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-67)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -49,   406,    24,   -67,   -49,   -67,     1,    12,   -67,   -67,
     -67,   -29,   -67,   429,   367,   -67,   429,    28,   -27,   -67,
      35,    15,    23,   -67,   -67,   -67,   -67,   -67,   -67,   -67,
      42,    21,   -67,   -67,   -67,   225,   -67,    27,    12,   -67,
     167,   -67,   -67,   -67,   -67,   -67,    84,    85,     1,    86,
      88,   -46,   -67,    23,     1,   -67,     1,   -67,   -67,    36,
     -67,   361,   361,   361,    34,     6,   361,    12,     3,   361,
       9,   100,   361,   361,   361,     6,   361,   361,   361,   361,
     361,   361,   361,   361,   361,   361,   361,   361,   361,   361,
     361,   361,   361,   343,   361,    97,   361,   122,   -67,   -67,
     167,   284,   -67,    77,    78,    79,     1,     1,   429,   -67,
      87,    93,   -67,   429,   402,   167,   167,   125,   -67,   -67,
     113,   361,    94,   361,    95,    96,   -67,   361,   105,   -67,
     -67,   106,   129,   361,   361,   107,   361,   108,   115,   117,
     136,   137,   361,   361,   361,   361,   361,   361,   138,   158,
     361,   361,   361,   121,   361,   126,   361,   -67,   -67,   -67,
     134,   135,   426,   -67,   -67,   -67,    89,   139,   187,   -67,
     -67,   140,   -67,   -67,   -67,   361,   -67,   -67,   -67,   141,
     142,   -67,   143,   -67,   -67,   361,   361,   361,   144,   145,
     146,   148,   152,   153,   -67,   154,   -67,   155,   156,   159,
     164,   -67,   165,   -67,   176,   -67,   -67,   -67,   179,   -67,
     429,   183,    89,   -67,   -67,   -67,   202,   -67,   361,   -67,
     -67,   -67,   157,   222,   239,   -67,   -67,   -67,   -67,   -67,
     -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   -67,   177,
      12,   -67,   -67,   206,   361,   361,   361,   207,   208,   -67,
     231,   259,   253,   -67,   -67,   361,   361,   361,   237,   290,
     241,   -67,   361,   -67,   242,   -67
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     4,     3,     7,     0,    28,    84,    83,
     103,     0,    85,     0,     0,    23,     0,     0,    99,    86,
       0,   100,     0,     1,     5,     8,   104,   105,   106,   107,
       0,     0,    20,    19,   108,     0,    35,     0,    26,    29,
      27,    33,    36,    79,    56,    78,     0,     0,     0,     0,
       0,     0,    90,    91,     0,    87,    17,   101,   102,     0,
      16,     0,     0,     0,     0,     0,    52,    28,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    52,     0,     6,    30,
      25,     0,    34,     0,     0,     0,     0,    17,     0,    89,
       0,     0,    18,     0,     0,     0,     0,     0,    54,    74,
       0,     0,     0,    53,     0,     0,    40,     0,     0,    42,
      44,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    21,    13,    12,    11,
       0,     0,     0,    97,    15,    14,    92,     0,     0,    46,
      55,     0,    80,    24,    41,     0,    43,    45,    47,     0,
       0,    61,     0,    76,    77,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    58,     0,    57,     0,     0,     0,
       0,    71,     0,    81,     0,    22,    10,     9,     0,    98,
       0,     0,    93,    94,    39,    37,     0,    75,     0,    72,
      73,   109,     0,     0,     0,    67,    68,    70,    69,    66,
      65,    59,    60,    62,    63,    64,    32,    31,    88,     0,
      28,    95,    38,     0,     0,     0,     0,     0,     0,    49,
       0,     0,     0,    96,    82,     0,     0,     0,     0,     0,
       0,    50,     0,    48,     0,    51
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -67,   -67,   295,   -67,   299,   198,    19,   -67,   -12,   -67,
     -66,   -67,   268,   269,   -32,   227,   -43,   -35,    16,   -67,
     310,   211,   -67,   -67,   114,   -67,    61,   -67,   -13,    70,
     -56
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     4,     5,   111,   112,   204,    17,    36,
      37,    38,    39,    40,    41,   122,   123,    42,    43,    18,
      19,    51,   211,   212,   213,   162,    52,    21,    22,    44,
      45
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      96,   124,    49,    53,    26,    27,   125,    28,   102,   121,
       1,    34,   128,   108,   109,    26,    27,    34,    28,   135,
     117,    29,    32,    95,    23,    31,   115,   116,   118,   132,
      16,   118,    29,    54,   127,    55,   131,   118,   133,   134,
      56,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,    96,   153,
      30,   118,    20,   126,    32,   120,    96,   105,   102,   129,
      32,    35,    32,   110,    47,    50,    33,    57,    59,    96,
      53,    60,   170,   167,   168,    58,   171,    98,   170,   103,
     104,   106,   175,   107,   119,   113,    97,   170,   179,   180,
      53,   182,   154,    26,    27,    34,    28,   188,   189,   190,
     191,   192,   193,   195,   197,   198,   199,   200,    33,   202,
      29,   205,    32,    32,    33,   160,    33,   156,    26,    27,
      34,    28,    26,    27,    34,    28,   216,   157,   158,   159,
     218,    26,    27,    34,    28,    29,    76,   164,   210,    29,
     222,   223,   224,   165,   172,   173,   174,   185,    29,   114,
     130,    26,    27,    34,    28,   176,   177,   181,   183,   163,
      26,    27,    34,    28,   248,   184,    33,    33,    29,   186,
     187,   201,   247,   243,   114,   169,   203,    29,   114,   178,
      26,    27,    34,    28,   206,   207,   244,   114,   194,   214,
     217,   219,   220,   221,   225,   226,   227,    29,   228,   250,
     251,   252,   229,   230,   231,   232,   233,   114,   196,   234,
     258,   259,   260,   209,   235,   236,   101,   264,    26,    27,
      34,    28,    61,    62,    63,    64,   237,    65,     8,   238,
       9,    66,    10,   240,    12,    29,   101,   215,    15,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    59,   242,    79,   245,   246,   249,   253,   254,    80,
      81,   239,   255,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,   256,    94,    26,    27,    34,
      28,    61,    62,    63,    64,   257,    65,   261,   262,    24,
      66,   263,   265,    25,    29,   161,    99,   100,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      59,    46,    79,   155,   166,     0,   241,     0,    80,    81,
       0,     0,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,   114,     0,    94,    26,    27,    34,    28,
       0,     0,     0,    64,     0,    65,     8,     0,     9,    66,
      10,     0,    12,    29,    26,    27,    34,    28,     0,     0,
       0,     0,    48,    73,    74,    75,    76,    77,    78,    59,
       8,    29,     9,     0,    10,     0,    12,     0,     0,     0,
      15,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,     0,    94,    26,    27,    34,    28,     0,
       0,     6,    64,     0,    65,     0,     0,     7,    66,     8,
     114,     9,    29,    10,    11,    12,    16,    13,    14,    15,
       0,     0,    73,    74,    75,    76,    77,    78,    59,     8,
       0,     9,     8,    10,     9,    12,    10,     0,    12,     0,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,   114,     0,    94,     0,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    16,   208,     0,    16
};

static const yytype_int16 yycheck[] =
{
      35,    67,    14,    16,     3,     4,     3,     6,    40,    65,
      59,     5,     3,    59,    60,     3,     4,     5,     6,    75,
      63,    20,     6,    35,     0,     6,    61,    62,    63,    72,
      59,    66,    20,     5,    69,    62,    71,    72,    73,    74,
       5,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      59,    96,     1,    60,    48,    59,   101,    48,   100,    60,
      54,    59,    56,    54,    13,    14,     6,    62,    36,   114,
      93,    60,   117,   115,   116,    62,   121,    60,   123,     5,
       5,     5,   127,     5,    60,    59,    35,   132,   133,   134,
     113,   136,     5,     3,     4,     5,     6,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,    48,   154,
      20,   156,   106,   107,    54,   106,    56,     5,     3,     4,
       5,     6,     3,     4,     5,     6,   168,    60,    60,    60,
     175,     3,     4,     5,     6,    20,    33,    60,    59,    20,
     185,   186,   187,    60,    60,    60,    60,    40,    20,    59,
      60,     3,     4,     5,     6,    60,    60,    60,    60,   108,
       3,     4,     5,     6,   240,    60,   106,   107,    20,    43,
      43,    60,     5,   218,    59,    60,    60,    20,    59,    60,
       3,     4,     5,     6,    60,    60,    39,    59,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    20,    60,   244,
     245,   246,    60,    60,    60,    60,    60,    59,    60,    60,
     255,   256,   257,   162,    60,    60,    59,   262,     3,     4,
       5,     6,     7,     8,     9,    10,    60,    12,    13,    60,
      15,    16,    17,    60,    19,    20,    59,    60,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    60,    38,    42,    26,    60,    60,    60,    44,
      45,   210,    41,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    26,    61,     3,     4,     5,
       6,     7,     8,     9,    10,    42,    12,    60,     8,     4,
      16,    60,    60,     4,    20,   107,    38,    38,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    11,    38,    96,   113,    -1,   212,    -1,    44,    45,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    61,     3,     4,     5,     6,
      -1,    -1,    -1,    10,    -1,    12,    13,    -1,    15,    16,
      17,    -1,    19,    20,     3,     4,     5,     6,    -1,    -1,
      -1,    -1,     5,    30,    31,    32,    33,    34,    35,    36,
      13,    20,    15,    -1,    17,    -1,    19,    -1,    -1,    -1,
      23,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    61,     3,     4,     5,     6,    -1,
      -1,     5,    10,    -1,    12,    -1,    -1,    11,    16,    13,
      59,    15,    20,    17,    18,    19,    59,    21,    22,    23,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    13,
      -1,    15,    13,    17,    15,    19,    17,    -1,    19,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    61,    -1,    59,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    60,    -1,    59
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    59,    64,    65,    66,    67,     5,    11,    13,    15,
      17,    18,    19,    21,    22,    23,    59,    71,    82,    83,
      89,    90,    91,     0,    65,    67,     3,     4,     6,    20,
      59,    69,    81,    92,     5,    59,    72,    73,    74,    75,
      76,    77,    80,    81,    92,    93,    83,    89,     5,    71,
      89,    84,    89,    91,     5,    62,     5,    62,    62,    36,
      60,     7,     8,     9,    10,    12,    16,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    38,
      44,    45,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    61,    71,    80,    89,    60,    75,
      76,    59,    77,     5,     5,    69,     5,     5,    59,    60,
      69,    68,    69,    59,    59,    80,    80,    79,    80,    60,
      59,    93,    78,    79,    73,     3,    60,    80,     3,    60,
      60,    80,    79,    80,    80,    93,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,     5,    78,     5,    60,    60,    60,
      69,    68,    88,    89,    60,    60,    84,    77,    77,    60,
      80,    80,    60,    60,    60,    80,    60,    60,    60,    80,
      80,    60,    80,    60,    60,    40,    43,    43,    80,    80,
      80,    80,    80,    80,    60,    80,    60,    80,    80,    80,
      80,    60,    80,    60,    70,    80,    60,    60,    60,    89,
      59,    85,    86,    87,    60,    60,    77,    60,    80,    60,
      60,    60,    80,    80,    80,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    89,
      60,    87,    60,    80,    39,    42,    26,     5,    73,    60,
      80,    80,    80,    60,    60,    41,    26,    42,    80,    80,
      80,    60,     8,    60,    80,    60
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    63,    64,    64,    64,    64,    65,    66,    66,    67,
      67,    67,    67,    67,    67,    67,    67,    68,    68,    69,
      69,    70,    70,    71,    72,    73,    73,    73,    73,    74,
      74,    75,    75,    76,    76,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    78,    78,    79,    79,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    81,    82,    82,    82,    82,    82,    83,    83,
      84,    84,    85,    85,    86,    86,    87,    88,    88,    89,
      89,    90,    90,    91,    92,    92,    92,    92,    93,    93
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     4,     1,     2,     6,
       6,     5,     5,     5,     5,     5,     4,     0,     1,     1,
       1,     0,     1,     1,     4,     2,     1,     1,     0,     1,
       2,     5,     5,     1,     2,     1,     1,     5,     6,     5,
       3,     4,     3,     4,     3,     4,     4,     4,    10,     7,
      10,    12,     0,     1,     1,     2,     1,     4,     4,     5,
       5,     4,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     4,     5,     5,     3,     5,     4,     4,     1,     1,
       4,     4,     8,     1,     1,     1,     1,     2,     6,     3,
       1,     1,     0,     1,     1,     2,     4,     1,     2,     1,
       1,     2,     2,     1,     1,     1,     1,     1,     1,     5
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
        yyerror (compiler, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, compiler); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, std::shared_ptr<cdk::compiler> compiler)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (compiler);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, std::shared_ptr<cdk::compiler> compiler)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, compiler);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, std::shared_ptr<cdk::compiler> compiler)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], compiler);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, compiler); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, std::shared_ptr<cdk::compiler> compiler)
{
  YY_USE (yyvaluep);
  YY_USE (compiler);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (std::shared_ptr<cdk::compiler> compiler)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* file: %empty  */
#line 72 "til_parser.y"
                                                  { compiler->ast((yyval.sequence) = new cdk::sequence_node(LINE)); }
#line 1387 "til_parser.tab.c"
    break;

  case 3: /* file: global_declarations  */
#line 73 "til_parser.y"
                                                  { compiler->ast((yyval.sequence) = (yyvsp[0].sequence)); }
#line 1393 "til_parser.tab.c"
    break;

  case 4: /* file: main  */
#line 74 "til_parser.y"
                                                  { compiler->ast((yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[0].node))); }
#line 1399 "til_parser.tab.c"
    break;

  case 5: /* file: global_declarations main  */
#line 75 "til_parser.y"
                                                  { compiler->ast((yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[0].node), (yyvsp[-1].sequence))); }
#line 1405 "til_parser.tab.c"
    break;

  case 6: /* main: '(' tPROGRAM block_content ')'  */
#line 78 "til_parser.y"
                                                  { (yyval.node) = new til::function_definition_node(LINE, (yyvsp[-1].block)); }
#line 1411 "til_parser.tab.c"
    break;

  case 7: /* global_declarations: global_declaration  */
#line 81 "til_parser.y"
                                                                      { (yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[0].node)); }
#line 1417 "til_parser.tab.c"
    break;

  case 8: /* global_declarations: global_declarations global_declaration  */
#line 82 "til_parser.y"
                                                                      { (yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[0].node), (yyvsp[-1].sequence)); }
#line 1423 "til_parser.tab.c"
    break;

  case 9: /* global_declaration: '(' tPUBLIC var_type tIDENTIFIER opt_global_init ')'  */
#line 85 "til_parser.y"
                                                                                  { (yyval.node) = new til::declaration_node(LINE, tPUBLIC, (yyvsp[-3].type), *(yyvsp[-2].s), (yyvsp[-1].expression)); delete (yyvsp[-2].s); }
#line 1429 "til_parser.tab.c"
    break;

  case 10: /* global_declaration: '(' tPUBLIC var tIDENTIFIER global_init ')'  */
#line 86 "til_parser.y"
                                                                                  { (yyval.node) = new til::declaration_node(LINE, tPUBLIC, (yyvsp[-3].type), *(yyvsp[-2].s), (yyvsp[-1].expression)); delete (yyvsp[-2].s); }
#line 1435 "til_parser.tab.c"
    break;

  case 11: /* global_declaration: '(' tPUBLIC tIDENTIFIER global_init ')'  */
#line 87 "til_parser.y"
                                                                                  { (yyval.node) = new til::declaration_node(LINE, tPUBLIC, nullptr, *(yyvsp[-2].s), (yyvsp[-1].expression)); delete (yyvsp[-2].s); }
#line 1441 "til_parser.tab.c"
    break;

  case 12: /* global_declaration: '(' tFORWARD var_type tIDENTIFIER ')'  */
#line 88 "til_parser.y"
                                                                                  { (yyval.node) = new til::declaration_node(LINE, tFORWARD, (yyvsp[-2].type), *(yyvsp[-1].s), nullptr); delete (yyvsp[-1].s); }
#line 1447 "til_parser.tab.c"
    break;

  case 13: /* global_declaration: '(' tEXTERNAL fun_type tIDENTIFIER ')'  */
#line 89 "til_parser.y"
                                                                                  { (yyval.node) = new til::declaration_node(LINE, tEXTERNAL, (yyvsp[-2].type), *(yyvsp[-1].s), nullptr); delete (yyvsp[-1].s); }
#line 1453 "til_parser.tab.c"
    break;

  case 14: /* global_declaration: '(' var_type tIDENTIFIER opt_global_init ')'  */
#line 90 "til_parser.y"
                                                                                  { (yyval.node) = new til::declaration_node(LINE, tPRIVATE, (yyvsp[-3].type), *(yyvsp[-2].s), (yyvsp[-1].expression)); delete (yyvsp[-2].s); }
#line 1459 "til_parser.tab.c"
    break;

  case 15: /* global_declaration: '(' var tIDENTIFIER global_init ')'  */
#line 91 "til_parser.y"
                                                                                  { (yyval.node) = new til::declaration_node(LINE, tPRIVATE, (yyvsp[-3].type), *(yyvsp[-2].s), (yyvsp[-1].expression)); delete (yyvsp[-2].s); }
#line 1465 "til_parser.tab.c"
    break;

  case 16: /* global_declaration: '(' tIDENTIFIER global_init ')'  */
#line 92 "til_parser.y"
                                                                                  { (yyval.node) = new til::declaration_node(LINE, tPRIVATE, nullptr, *(yyvsp[-2].s), (yyvsp[-1].expression)); delete (yyvsp[-2].s); }
#line 1471 "til_parser.tab.c"
    break;

  case 17: /* opt_global_init: %empty  */
#line 95 "til_parser.y"
                                          { (yyval.expression) = nullptr; }
#line 1477 "til_parser.tab.c"
    break;

  case 18: /* opt_global_init: global_init  */
#line 96 "til_parser.y"
                                          { (yyval.expression) = (yyvsp[0].expression); }
#line 1483 "til_parser.tab.c"
    break;

  case 19: /* global_init: literal  */
#line 99 "til_parser.y"
                                          { (yyval.expression) = (yyvsp[0].expression); }
#line 1489 "til_parser.tab.c"
    break;

  case 20: /* global_init: fundef  */
#line 100 "til_parser.y"
                                          { (yyval.expression) = (yyvsp[0].expression); }
#line 1495 "til_parser.tab.c"
    break;

  case 21: /* opt_init: %empty  */
#line 103 "til_parser.y"
                                          { (yyval.expression) = nullptr; }
#line 1501 "til_parser.tab.c"
    break;

  case 22: /* opt_init: expr  */
#line 104 "til_parser.y"
                                          { (yyval.expression) = (yyvsp[0].expression); }
#line 1507 "til_parser.tab.c"
    break;

  case 23: /* var: tVAR  */
#line 107 "til_parser.y"
                                          { (yyval.type) = cdk::primitive_type::create(0, cdk::TYPE_UNSPEC); }
#line 1513 "til_parser.tab.c"
    break;

  case 24: /* block: '(' tBLOCK block_content ')'  */
#line 110 "til_parser.y"
                                                        { (yyval.block) = (yyvsp[-1].block); }
#line 1519 "til_parser.tab.c"
    break;

  case 25: /* block_content: declarations instrs  */
#line 113 "til_parser.y"
                                                        { (yyval.block) = new til::block_node(LINE, (yyvsp[-1].sequence), (yyvsp[0].sequence)); }
#line 1525 "til_parser.tab.c"
    break;

  case 26: /* block_content: declarations  */
#line 114 "til_parser.y"
                                                        { (yyval.block) = new til::block_node(LINE, (yyvsp[0].sequence), nullptr); }
#line 1531 "til_parser.tab.c"
    break;

  case 27: /* block_content: instrs  */
#line 115 "til_parser.y"
                                                        { (yyval.block) = new til::block_node(LINE, nullptr, (yyvsp[0].sequence)); }
#line 1537 "til_parser.tab.c"
    break;

  case 28: /* block_content: %empty  */
#line 116 "til_parser.y"
                                                        { (yyval.block) = new til::block_node(LINE, nullptr, nullptr); }
#line 1543 "til_parser.tab.c"
    break;

  case 29: /* declarations: declaration  */
#line 119 "til_parser.y"
                                                          { (yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[0].node)); }
#line 1549 "til_parser.tab.c"
    break;

  case 30: /* declarations: declarations declaration  */
#line 120 "til_parser.y"
                                                        { (yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[0].node), (yyvsp[-1].sequence)); }
#line 1555 "til_parser.tab.c"
    break;

  case 31: /* declaration: '(' var_type tIDENTIFIER opt_init ')'  */
#line 123 "til_parser.y"
                                                        { (yyval.node) = new til::declaration_node(LINE, tPRIVATE, (yyvsp[-3].type), *(yyvsp[-2].s), (yyvsp[-1].expression)); delete (yyvsp[-2].s); }
#line 1561 "til_parser.tab.c"
    break;

  case 32: /* declaration: '(' var tIDENTIFIER expr ')'  */
#line 124 "til_parser.y"
                                                        { (yyval.node) = new til::declaration_node(LINE, tPRIVATE, (yyvsp[-3].type), *(yyvsp[-2].s), (yyvsp[-1].expression)); delete (yyvsp[-2].s); }
#line 1567 "til_parser.tab.c"
    break;

  case 33: /* instrs: instr  */
#line 127 "til_parser.y"
                                             { (yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[0].node)); }
#line 1573 "til_parser.tab.c"
    break;

  case 34: /* instrs: instrs instr  */
#line 128 "til_parser.y"
                                             { (yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[0].node), (yyvsp[-1].sequence)); }
#line 1579 "til_parser.tab.c"
    break;

  case 35: /* instr: block  */
#line 131 "til_parser.y"
                                             { (yyval.node) = (yyvsp[0].block); }
#line 1585 "til_parser.tab.c"
    break;

  case 36: /* instr: expr  */
#line 132 "til_parser.y"
                                             { (yyval.node) = new til::evaluation_node(LINE, (yyvsp[0].expression)); }
#line 1591 "til_parser.tab.c"
    break;

  case 37: /* instr: '(' tIF expr instr ')'  */
#line 133 "til_parser.y"
                                             { (yyval.node) = new til::if_node(LINE, (yyvsp[-2].expression), (yyvsp[-1].node)); }
#line 1597 "til_parser.tab.c"
    break;

  case 38: /* instr: '(' tIF expr instr instr ')'  */
#line 134 "til_parser.y"
                                             { (yyval.node) = new til::if_else_node(LINE, (yyvsp[-3].expression), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 1603 "til_parser.tab.c"
    break;

  case 39: /* instr: '(' tLOOP expr instr ')'  */
#line 135 "til_parser.y"
                                             { (yyval.node) = new til::loop_node(LINE, (yyvsp[-2].expression), (yyvsp[-1].node)); }
#line 1609 "til_parser.tab.c"
    break;

  case 40: /* instr: '(' tSTOP ')'  */
#line 136 "til_parser.y"
                                             { (yyval.node) = new til::stop_node(LINE); }
#line 1615 "til_parser.tab.c"
    break;

  case 41: /* instr: '(' tSTOP tINTEGER ')'  */
#line 137 "til_parser.y"
                                             { (yyval.node) = new til::stop_node(LINE, (yyvsp[-1].i)); }
#line 1621 "til_parser.tab.c"
    break;

  case 42: /* instr: '(' tNEXT ')'  */
#line 138 "til_parser.y"
                                             { (yyval.node) = new til::next_node(LINE); }
#line 1627 "til_parser.tab.c"
    break;

  case 43: /* instr: '(' tNEXT tINTEGER ')'  */
#line 139 "til_parser.y"
                                             { (yyval.node) = new til::next_node(LINE, (yyvsp[-1].i)); }
#line 1633 "til_parser.tab.c"
    break;

  case 44: /* instr: '(' tRETURN ')'  */
#line 140 "til_parser.y"
                                             { (yyval.node) = new til::return_node(LINE); }
#line 1639 "til_parser.tab.c"
    break;

  case 45: /* instr: '(' tRETURN expr ')'  */
#line 141 "til_parser.y"
                                             { (yyval.node) = new til::return_node(LINE, (yyvsp[-1].expression)); }
#line 1645 "til_parser.tab.c"
    break;

  case 46: /* instr: '(' tPRINT exprs ')'  */
#line 142 "til_parser.y"
                                             { (yyval.node) = new til::print_node(LINE, (yyvsp[-1].sequence), false); }
#line 1651 "til_parser.tab.c"
    break;

  case 47: /* instr: '(' tPRINTLN exprs ')'  */
#line 143 "til_parser.y"
                                             { (yyval.node) = new til::print_node(LINE, (yyvsp[-1].sequence), true); }
#line 1657 "til_parser.tab.c"
    break;

  case 48: /* instr: '(' tCHANGE expr tARROW expr tWITH expr tDOTS expr ')'  */
#line 144 "til_parser.y"
                                                                             { (yyval.node) = new til::change_node(LINE, (yyvsp[-7].expression), (yyvsp[-5].expression), (yyvsp[-3].expression), (yyvsp[-1].expression)); }
#line 1663 "til_parser.tab.c"
    break;

  case 49: /* instr: '(' tWITH expr expr expr expr ')'  */
#line 145 "til_parser.y"
                                             { (yyval.node) = new til::with_node(LINE, (yyvsp[-4].expression), (yyvsp[-3].expression), (yyvsp[-2].expression), (yyvsp[-1].expression));}
#line 1669 "til_parser.tab.c"
    break;

  case 50: /* instr: '(' tUNLESS expr tFOR expr tDO expr tAPPLY expr ')'  */
#line 146 "til_parser.y"
                                                                       { (yyval.node) = new til::unless_node(LINE, (yyvsp[-7].expression), (yyvsp[-5].expression), (yyvsp[-3].expression), (yyvsp[-1].expression));}
#line 1675 "til_parser.tab.c"
    break;

  case 51: /* instr: '(' tSWEEP expr tARROW expr tDOTS expr tWITH expr tIF expr ')'  */
#line 147 "til_parser.y"
                                                                       { (yyval.node) = new til::sweep_node(LINE, (yyvsp[-9].expression), (yyvsp[-7].expression), (yyvsp[-5].expression), (yyvsp[-3].expression), (yyvsp[-1].expression));}
#line 1681 "til_parser.tab.c"
    break;

  case 52: /* opt_exprs: %empty  */
#line 150 "til_parser.y"
                                             { (yyval.sequence) = nullptr; }
#line 1687 "til_parser.tab.c"
    break;

  case 53: /* opt_exprs: exprs  */
#line 151 "til_parser.y"
                                             { (yyval.sequence) = (yyvsp[0].sequence); }
#line 1693 "til_parser.tab.c"
    break;

  case 54: /* exprs: expr  */
#line 154 "til_parser.y"
                                             { (yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[0].expression)); }
#line 1699 "til_parser.tab.c"
    break;

  case 55: /* exprs: exprs expr  */
#line 155 "til_parser.y"
                                             { (yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[0].expression), (yyvsp[-1].sequence)); }
#line 1705 "til_parser.tab.c"
    break;

  case 56: /* expr: literal  */
#line 158 "til_parser.y"
                                             { (yyval.expression) = (yyvsp[0].expression); }
#line 1711 "til_parser.tab.c"
    break;

  case 57: /* expr: '(' '-' expr ')'  */
#line 159 "til_parser.y"
                                             { (yyval.expression) = new cdk::unary_minus_node(LINE, (yyvsp[-1].expression)); }
#line 1717 "til_parser.tab.c"
    break;

  case 58: /* expr: '(' '+' expr ')'  */
#line 160 "til_parser.y"
                                             { (yyval.expression) = new cdk::unary_plus_node(LINE, (yyvsp[-1].expression)); }
#line 1723 "til_parser.tab.c"
    break;

  case 59: /* expr: '(' '+' expr expr ')'  */
#line 161 "til_parser.y"
                                             { (yyval.expression) = new cdk::add_node(LINE, (yyvsp[-2].expression), (yyvsp[-1].expression)); }
#line 1729 "til_parser.tab.c"
    break;

  case 60: /* expr: '(' '-' expr expr ')'  */
#line 162 "til_parser.y"
                                             { (yyval.expression) = new cdk::sub_node(LINE, (yyvsp[-2].expression), (yyvsp[-1].expression)); }
#line 1735 "til_parser.tab.c"
    break;

  case 61: /* expr: '(' tFIND lval ')'  */
#line 163 "til_parser.y"
                                             { (yyval.expression) = new til::address_of_node(LINE, (yyvsp[-1].lvalue)); }
#line 1741 "til_parser.tab.c"
    break;

  case 62: /* expr: '(' '*' expr expr ')'  */
#line 164 "til_parser.y"
                                             { (yyval.expression) = new cdk::mul_node(LINE, (yyvsp[-2].expression), (yyvsp[-1].expression)); }
#line 1747 "til_parser.tab.c"
    break;

  case 63: /* expr: '(' '/' expr expr ')'  */
#line 165 "til_parser.y"
                                             { (yyval.expression) = new cdk::div_node(LINE, (yyvsp[-2].expression), (yyvsp[-1].expression)); }
#line 1753 "til_parser.tab.c"
    break;

  case 64: /* expr: '(' '%' expr expr ')'  */
#line 166 "til_parser.y"
                                             { (yyval.expression) = new cdk::mod_node(LINE, (yyvsp[-2].expression), (yyvsp[-1].expression)); }
#line 1759 "til_parser.tab.c"
    break;

  case 65: /* expr: '(' '<' expr expr ')'  */
#line 167 "til_parser.y"
                                             { (yyval.expression) = new cdk::lt_node(LINE, (yyvsp[-2].expression), (yyvsp[-1].expression)); }
#line 1765 "til_parser.tab.c"
    break;

  case 66: /* expr: '(' '>' expr expr ')'  */
#line 168 "til_parser.y"
                                             { (yyval.expression) = new cdk::gt_node(LINE, (yyvsp[-2].expression), (yyvsp[-1].expression)); }
#line 1771 "til_parser.tab.c"
    break;

  case 67: /* expr: '(' tGE expr expr ')'  */
#line 169 "til_parser.y"
                                             { (yyval.expression) = new cdk::ge_node(LINE, (yyvsp[-2].expression), (yyvsp[-1].expression)); }
#line 1777 "til_parser.tab.c"
    break;

  case 68: /* expr: '(' tLE expr expr ')'  */
#line 170 "til_parser.y"
                                             { (yyval.expression) = new cdk::le_node(LINE, (yyvsp[-2].expression), (yyvsp[-1].expression)); }
#line 1783 "til_parser.tab.c"
    break;

  case 69: /* expr: '(' tNE expr expr ')'  */
#line 171 "til_parser.y"
                                             { (yyval.expression) = new cdk::ne_node(LINE, (yyvsp[-2].expression), (yyvsp[-1].expression)); }
#line 1789 "til_parser.tab.c"
    break;

  case 70: /* expr: '(' tEQ expr expr ')'  */
#line 172 "til_parser.y"
                                             { (yyval.expression) = new cdk::eq_node(LINE, (yyvsp[-2].expression), (yyvsp[-1].expression)); }
#line 1795 "til_parser.tab.c"
    break;

  case 71: /* expr: '(' '~' expr ')'  */
#line 173 "til_parser.y"
                                             { (yyval.expression) = new cdk::not_node(LINE, (yyvsp[-1].expression)); }
#line 1801 "til_parser.tab.c"
    break;

  case 72: /* expr: '(' tAND expr expr ')'  */
#line 174 "til_parser.y"
                                             { (yyval.expression) = new cdk::and_node(LINE, (yyvsp[-2].expression), (yyvsp[-1].expression)); }
#line 1807 "til_parser.tab.c"
    break;

  case 73: /* expr: '(' tOR expr expr ')'  */
#line 175 "til_parser.y"
                                             { (yyval.expression) = new cdk::or_node(LINE, (yyvsp[-2].expression), (yyvsp[-1].expression)); }
#line 1813 "til_parser.tab.c"
    break;

  case 74: /* expr: '(' tREAD ')'  */
#line 176 "til_parser.y"
                                             { (yyval.expression) = new til::read_node(LINE); }
#line 1819 "til_parser.tab.c"
    break;

  case 75: /* expr: '(' tSET lval expr ')'  */
#line 177 "til_parser.y"
                                             { (yyval.expression) = new cdk::assignment_node(LINE, (yyvsp[-2].lvalue), (yyvsp[-1].expression)); }
#line 1825 "til_parser.tab.c"
    break;

  case 76: /* expr: '(' tOBJECTS expr ')'  */
#line 178 "til_parser.y"
                                             { (yyval.expression) = new til::stack_alloc_node(LINE, (yyvsp[-1].expression)); }
#line 1831 "til_parser.tab.c"
    break;

  case 77: /* expr: '(' tSIZEOF expr ')'  */
#line 179 "til_parser.y"
                                             { (yyval.expression) = new til::sizeof_node(LINE, (yyvsp[-1].expression)); }
#line 1837 "til_parser.tab.c"
    break;

  case 78: /* expr: lval  */
#line 180 "til_parser.y"
                                             { (yyval.expression) = new cdk::rvalue_node(LINE, (yyvsp[0].lvalue)); }
#line 1843 "til_parser.tab.c"
    break;

  case 79: /* expr: fundef  */
#line 181 "til_parser.y"
                                             { (yyval.expression) = (yyvsp[0].expression); }
#line 1849 "til_parser.tab.c"
    break;

  case 80: /* expr: '(' tAT opt_exprs ')'  */
#line 182 "til_parser.y"
                                             { (yyval.expression) = new til::function_call_node(LINE, nullptr, (yyvsp[-1].sequence)); }
#line 1855 "til_parser.tab.c"
    break;

  case 81: /* expr: '(' expr opt_exprs ')'  */
#line 183 "til_parser.y"
                                             { (yyval.expression) = new til::function_call_node(LINE, (yyvsp[-2].expression), (yyvsp[-1].sequence)); }
#line 1861 "til_parser.tab.c"
    break;

  case 82: /* fundef: '(' tFUNCTION '(' return_type opt_args ')' block_content ')'  */
#line 186 "til_parser.y"
                                                                       {
      (yyval.expression) = new til::function_definition_node(LINE, (yyvsp[-4].type), (yyvsp[-3].sequence), (yyvsp[-1].block));
      }
#line 1869 "til_parser.tab.c"
    break;

  case 83: /* data_type: tTYPE_STRING  */
#line 191 "til_parser.y"
                                             { (yyval.type) = cdk::primitive_type::create(4, cdk::TYPE_STRING); }
#line 1875 "til_parser.tab.c"
    break;

  case 84: /* data_type: tTYPE_INT  */
#line 192 "til_parser.y"
                                             { (yyval.type) = cdk::primitive_type::create(4, cdk::TYPE_INT); }
#line 1881 "til_parser.tab.c"
    break;

  case 85: /* data_type: tTYPE_DOUBLE  */
#line 193 "til_parser.y"
                                             { (yyval.type) = cdk::primitive_type::create(8, cdk::TYPE_DOUBLE); }
#line 1887 "til_parser.tab.c"
    break;

  case 86: /* data_type: fun_type  */
#line 194 "til_parser.y"
                                             { (yyval.type) = (yyvsp[0].type); }
#line 1893 "til_parser.tab.c"
    break;

  case 87: /* data_type: data_type '!'  */
#line 195 "til_parser.y"
                                             { (yyval.type) = cdk::reference_type::create(4, (yyvsp[-1].type)); }
#line 1899 "til_parser.tab.c"
    break;

  case 88: /* fun_type: '(' return_type '(' var_types ')' ')'  */
#line 198 "til_parser.y"
                                                     { (yyval.type) = cdk::functional_type::create(*(yyvsp[-2].types), (yyvsp[-4].type)); delete (yyvsp[-2].types); }
#line 1905 "til_parser.tab.c"
    break;

  case 89: /* fun_type: '(' return_type ')'  */
#line 199 "til_parser.y"
                                                     { (yyval.type) = cdk::functional_type::create((yyvsp[-1].type)); }
#line 1911 "til_parser.tab.c"
    break;

  case 90: /* return_type: var_type  */
#line 202 "til_parser.y"
                                             { (yyval.type) = (yyvsp[0].type); }
#line 1917 "til_parser.tab.c"
    break;

  case 91: /* return_type: void_type  */
#line 203 "til_parser.y"
                                             { (yyval.type) = (yyvsp[0].type); }
#line 1923 "til_parser.tab.c"
    break;

  case 92: /* opt_args: %empty  */
#line 206 "til_parser.y"
                                             { (yyval.sequence) = new cdk::sequence_node(LINE); }
#line 1929 "til_parser.tab.c"
    break;

  case 93: /* opt_args: args  */
#line 207 "til_parser.y"
                                             { (yyval.sequence) = (yyvsp[0].sequence); }
#line 1935 "til_parser.tab.c"
    break;

  case 94: /* args: arg  */
#line 210 "til_parser.y"
                                             { (yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[0].node)); }
#line 1941 "til_parser.tab.c"
    break;

  case 95: /* args: args arg  */
#line 211 "til_parser.y"
                                             { (yyval.sequence) = new cdk::sequence_node(LINE, (yyvsp[0].node), (yyvsp[-1].sequence)); }
#line 1947 "til_parser.tab.c"
    break;

  case 96: /* arg: '(' var_type tIDENTIFIER ')'  */
#line 214 "til_parser.y"
                                             { (yyval.node) = new til::declaration_node(LINE, tPRIVATE, (yyvsp[-2].type), *(yyvsp[-1].s), NULL); delete (yyvsp[-1].s); }
#line 1953 "til_parser.tab.c"
    break;

  case 97: /* var_types: var_type  */
#line 217 "til_parser.y"
                                             { (yyval.types) = new std::vector<std::shared_ptr<cdk::basic_type>>(); (yyval.types)->push_back((yyvsp[0].type)); }
#line 1959 "til_parser.tab.c"
    break;

  case 98: /* var_types: var_types var_type  */
#line 218 "til_parser.y"
                                             { (yyval.types) = (yyvsp[-1].types); (yyval.types)->push_back((yyvsp[0].type)); }
#line 1965 "til_parser.tab.c"
    break;

  case 99: /* var_type: data_type  */
#line 221 "til_parser.y"
                                             { (yyval.type) = (yyvsp[0].type); }
#line 1971 "til_parser.tab.c"
    break;

  case 100: /* var_type: void_pointer  */
#line 222 "til_parser.y"
                                             { (yyval.type) = (yyvsp[0].type); }
#line 1977 "til_parser.tab.c"
    break;

  case 101: /* void_pointer: void_pointer '!'  */
#line 225 "til_parser.y"
                                             { (yyval.type) = cdk::reference_type::create(4, (yyvsp[-1].type)); }
#line 1983 "til_parser.tab.c"
    break;

  case 102: /* void_pointer: void_type '!'  */
#line 226 "til_parser.y"
                                             { (yyval.type) = cdk::reference_type::create(4, (yyvsp[-1].type)); }
#line 1989 "til_parser.tab.c"
    break;

  case 103: /* void_type: tTYPE_VOID  */
#line 229 "til_parser.y"
                                             { (yyval.type) = cdk::primitive_type::create(4, cdk::TYPE_VOID); }
#line 1995 "til_parser.tab.c"
    break;

  case 104: /* literal: tINTEGER  */
#line 232 "til_parser.y"
                                             { (yyval.expression) = new cdk::integer_node(LINE, (yyvsp[0].i)); }
#line 2001 "til_parser.tab.c"
    break;

  case 105: /* literal: tDOUBLE  */
#line 233 "til_parser.y"
                                             { (yyval.expression) = new cdk::double_node(LINE, (yyvsp[0].d)); }
#line 2007 "til_parser.tab.c"
    break;

  case 106: /* literal: tSTRING  */
#line 234 "til_parser.y"
                                             { (yyval.expression) = new cdk::string_node(LINE, (yyvsp[0].s)); }
#line 2013 "til_parser.tab.c"
    break;

  case 107: /* literal: tNULLPTR  */
#line 235 "til_parser.y"
                                             { (yyval.expression) = new til::nullptr_node(LINE); }
#line 2019 "til_parser.tab.c"
    break;

  case 108: /* lval: tIDENTIFIER  */
#line 238 "til_parser.y"
                                             { (yyval.lvalue) = new cdk::variable_node(LINE, (yyvsp[0].s)); }
#line 2025 "til_parser.tab.c"
    break;

  case 109: /* lval: '(' tINDEX expr expr ')'  */
#line 239 "til_parser.y"
                                             { (yyval.lvalue) = new til::index_node(LINE, (yyvsp[-2].expression), (yyvsp[-1].expression)); }
#line 2031 "til_parser.tab.c"
    break;


#line 2035 "til_parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (compiler, YY_("syntax error"));
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
                      yytoken, &yylval, compiler);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, compiler);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (compiler, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, compiler);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, compiler);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 242 "til_parser.y"

