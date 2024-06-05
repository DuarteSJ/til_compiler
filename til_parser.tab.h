/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_TIL_PARSER_TAB_H_INCLUDED
# define YY_YY_TIL_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    tINTEGER = 258,                /* tINTEGER  */
    tDOUBLE = 259,                 /* tDOUBLE  */
    tIDENTIFIER = 260,             /* tIDENTIFIER  */
    tSTRING = 261,                 /* tSTRING  */
    tLOOP = 262,                   /* tLOOP  */
    tIF = 263,                     /* tIF  */
    tPRINT = 264,                  /* tPRINT  */
    tREAD = 265,                   /* tREAD  */
    tPROGRAM = 266,                /* tPROGRAM  */
    tSET = 267,                    /* tSET  */
    tTYPE_INT = 268,               /* tTYPE_INT  */
    tYPE_DOUBLE = 269,             /* tYPE_DOUBLE  */
    tTYPE_STRING = 270,            /* tTYPE_STRING  */
    tAT = 271,                     /* tAT  */
    tTYPE_VOID = 272,              /* tTYPE_VOID  */
    tEXTERNAL = 273,               /* tEXTERNAL  */
    tTYPE_DOUBLE = 274,            /* tTYPE_DOUBLE  */
    tNULLPTR = 275,                /* tNULLPTR  */
    tFORWARD = 276,                /* tFORWARD  */
    tPUBLIC = 277,                 /* tPUBLIC  */
    tVAR = 278,                    /* tVAR  */
    tBLOCK = 279,                  /* tBLOCK  */
    tSTOP = 280,                   /* tSTOP  */
    tWITH = 281,                   /* tWITH  */
    tNEXT = 282,                   /* tNEXT  */
    tRETURN = 283,                 /* tRETURN  */
    tPRINTLN = 284,                /* tPRINTLN  */
    tAND = 285,                    /* tAND  */
    tOR = 286,                     /* tOR  */
    tFIND = 287,                   /* tFIND  */
    tINDEX = 288,                  /* tINDEX  */
    tOBJECTS = 289,                /* tOBJECTS  */
    tSIZEOF = 290,                 /* tSIZEOF  */
    tFUNCTION = 291,               /* tFUNCTION  */
    tPRIVATE = 292,                /* tPRIVATE  */
    tUNLESS = 293,                 /* tUNLESS  */
    tDO = 294,                     /* tDO  */
    tFOR = 295,                    /* tFOR  */
    tAPPLY = 296,                  /* tAPPLY  */
    tDOTS = 297,                   /* tDOTS  */
    tARROW = 298,                  /* tARROW  */
    tSWEEP = 299,                  /* tSWEEP  */
    tCHANGE = 300,                 /* tCHANGE  */
    tIFX = 301,                    /* tIFX  */
    tELSE = 302,                   /* tELSE  */
    tGE = 303,                     /* tGE  */
    tLE = 304,                     /* tLE  */
    tEQ = 305,                     /* tEQ  */
    tNE = 306                      /* tNE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "til_parser.y"

  //--- don't change *any* of these: if you do, you'll break the compiler.
  YYSTYPE() : type(cdk::primitive_type::create(0, cdk::TYPE_VOID)) {}
  ~YYSTYPE() {}
  YYSTYPE(const YYSTYPE &other) { *this = other; }
  YYSTYPE& operator=(const YYSTYPE &other) { type = other.type; return *this; }

  std::shared_ptr<cdk::basic_type> type;        /* expression type */
  //-- don't change *any* of these --- END!

  int                   i;          /* integer value */
  double                d;          /* double value */
  std::string          *s;          /* symbol name or string literal */
  std::vector<std::shared_ptr<cdk::basic_type>> *types;

  cdk::basic_node      *node;       /* node pointer */
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression; /* expression nodes */
  cdk::lvalue_node     *lvalue;

  til::block_node      *block;


#line 139 "til_parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (std::shared_ptr<cdk::compiler> compiler);


#endif /* !YY_YY_TIL_PARSER_TAB_H_INCLUDED  */
