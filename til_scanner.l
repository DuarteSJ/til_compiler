%option c++ prefix="til_scanner_" outfile="til_scanner.cpp"
%option stack noyywrap yylineno 8bit debug
%{ 
// make relevant includes before including the parser's tab file
#include <string>
#include <sstream>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>
#include <cdk/ast/lvalue_node.h>
#include "til_parser.tab.h"

static std::ostringstream strlit;

// don't change this
#define yyerror LexerError
%}
%x X_COMMENT
%x X_STRING X_BACKSLASH X_STRING_SKIP
%%
  yydebug=1; set_debug(1);

  /* ====================================================================== */
  /* ====[                      3.2 - Comments                        ]==== */
  /* ====================================================================== */

";".*                 ; /* ignore comments */

"/*"                   yy_push_state(X_COMMENT);
<X_COMMENT>"/*"        yy_push_state(X_COMMENT); /* ignore nested comment */
<X_COMMENT>"*/"        yy_pop_state();
<X_COMMENT>.|"\n"      ;  /* ignore inside comments */

  /* ====================================================================== */
  /* ====[                      1 - Data Types                        ]==== */
  /* ====================================================================== */

"int"                  return tTYPE_INT; 
"double"               return tTYPE_DOUBLE; 
"string"               return tTYPE_STRING; 
"void"                 return tTYPE_VOID; 

  /* ====================================================================== */
  /* ====[                    4.5 - Global Symbols                    ]==== */
  /* ====================================================================== */

"external"             return tEXTERNAL; 
"forward"              return tFORWARD; 
"public"               return tPUBLIC; 

"var"                  return tVAR; 

  /* ====================================================================== */
  /* ====[                        6.1 - BLOCKS                        ]==== */
  /* ====================================================================== */

"block"                return tBLOCK; 

  /* ====================================================================== */
  /* ====[               6.2 - Conditional Instruction                ]==== */
  /* ====================================================================== */

"if"                   return tIF; 

  /* ====================================================================== */
  /* ====[                   6.3 - Loop Instruction                   ]==== */
  /* ====================================================================== */

"loop"                 return tLOOP; 

  /* ====================================================================== */
  /* ====[               6.4 - Termination Instruction                ]==== */
  /* ====================================================================== */

"stop"                return tSTOP; 

  /* ====================================================================== */
  /* ====[               6.5 - Continuation Instruction               ]==== */
  /* ====================================================================== */

"next"                return tNEXT; 

  /* ====================================================================== */
  /* ====[                  6.6 - Return Instruction                  ]==== */
  /* ====================================================================== */

"return"              return tRETURN; 

  /* ====================================================================== */
  /* ====[                  6.8 - Print Instructions                  ]==== */
  /* ====================================================================== */

"print"                return tPRINT; 
"println"              return tPRINTLN; 

  /* ====================================================================== */
  /* ====[                   7 - with Instruction                     ]==== */
  /* ====================================================================== */

"with"                 return tWITH;


"unless"               return tUNLESS;
"for"                  return tFOR;
"do"                   return tDO;
"apply"                return tAPPLY;

"sweep" return tSWEEP;
"->" return tARROW;
".." return tDOTS;

"change" return tCHANGE;
  /* ====================================================================== */
  /* ====[                  7 - Expression Operators                  ]==== */
  /* ====================================================================== */

"?"                    return tFIND;
">="                   return tGE; 
"<="                   return tLE; 
"=="                   return tEQ; 
"!="                   return tNE; 

"&&"                   return tAND; 
"||"                   return tOR; 

"read"                 return tREAD; 
"null"                 return tNULLPTR; 
"set"                  return tSET; 
"index"                return tINDEX; 
"objects"              return tOBJECTS; 
"sizeof"               return tSIZEOF; 
"function"             return tFUNCTION; 

[-+*/%~()<>!]           return *yytext;

  /* ====================================================================== */
  /* ====[                       5 - Functions                        ]==== */
  /* ====================================================================== */

"@"                    return tAT;
"program"              return tPROGRAM;


  /* ====================================================================== */
  /* ====[                   3.8.1 - Whole Numbers                    ]==== */
  /* ====================================================================== */

0|[1-9][0-9]*              { /* decimal */
                          try {
                            yylval.i = std::stoi(yytext, NULL, 10);
                            return tINTEGER;
                          } catch (const std::out_of_range &e) {
                            yyerror("integer out of range");
                          }
                        }

0x0*[a-fA-F1-9]+        { /* hexadecimal */
                          try {
                            yylval.i = std::stoi(yytext, NULL, 16);
                            return tINTEGER;
                          } catch (const std::out_of_range &e) {
                            yyerror("integer out of range");
                          }
                        }


  /* ====================================================================== */
  /* ====[                     3.8.2 - Real Numbers                   ]==== */
  /* ====================================================================== */


([0-9]*\.[0-9]+|[0-9]+\.[0-9]*)([eE][-+]?[0-9]+)? |
[0-9]+([eE][-+]?[0-9]+)                             {
                                                      try {
                                                        yylval.d = std::stod(yytext);
                                                        return tDOUBLE;
                                                      } catch (const std::out_of_range &e) {
                                                          yyerror("floatting point number out of range");
                                                      }
                                                    }

  /* ====================================================================== */
  /* ====[                      3.8.3 - Strings                       ]==== */
  /* ====================================================================== */

\"                    yy_push_state(X_STRING);
<X_STRING>\\          yy_push_state(X_BACKSLASH);
<X_STRING>\"          {
                        yylval.s = new std::string(strlit.str());
                        strlit.str("");
                        yy_pop_state();
                        return tSTRING;
                      }

<X_STRING>\0           yyerror("NULL byte in string");
<X_STRING>\n           yyerror("Newline in string");
<X_STRING>.            strlit << *yytext;

<X_BACKSLASH>n         strlit << '\n'; yy_pop_state();
<X_BACKSLASH>r         strlit << '\r'; yy_pop_state();
<X_BACKSLASH>t         strlit << '\t'; yy_pop_state();
<X_BACKSLASH>\"        strlit << '\"'; yy_pop_state();
<X_BACKSLASH>\\        strlit << '\\'; yy_pop_state();
<X_BACKSLASH>0         yy_push_state(X_STRING_SKIP);
<X_BACKSLASH>[0-7]{1,3}   {
                            try {
                              const int c = std::stoi(yytext, NULL, 8);
                              if (c > 255) {
                                yyerror("octal escape sequence out of range");
                              }
                              strlit << (char) c;
                              yy_pop_state(); 
                            } catch (const std::out_of_range &e) {
                              yyerror("octal escape sequence out of range");
                            }
                          }
<X_BACKSLASH>.         strlit << *yytext; yy_pop_state();

<X_STRING_SKIP>\\\"|\\\\   ;
<X_STRING_SKIP>\0          yyerror("NULL byte in string");
<X_STRING_SKIP>\n          yyerror("Newline in string");
<X_STRING_SKIP>\"          {
                              yylval.s = new std::string(strlit.str());
                              strlit.str("");
                              yy_pop_state(); yy_pop_state(); yy_pop_state(); /* X_STRING_SKIP, X_BACKSLASH, X_STRING */
                              return tSTRING;
                            }
<X_STRING_SKIP>.           ;


  /* ====================================================================== */
  /* ====[                     3.7 - Identifiers                      ]==== */
  /* ====================================================================== */

[A-Za-z][A-Za-z0-9]*  yylval.s = new std::string(yytext); return tIDENTIFIER;


  /* ====================================================================== */
  /* ====[                      3.1 - Whitespace                      ]==== */
  /* ====================================================================== */

[ \t\n\r]+               ; /* ignore whitespace */

  /* ====================================================================== */
  /* ====[              Raise Error on Unknown Character              ]==== */
  /* ====================================================================== */
.                      yyerror("Unknown character");

%%
