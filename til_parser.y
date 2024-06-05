%{
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
%}

%parse-param {std::shared_ptr<cdk::compiler> compiler}

%union {
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

};

%token <i> tINTEGER
%token <d> tDOUBLE
%token <s> tIDENTIFIER tSTRING

%token tLOOP tIF tPRINT tREAD tPROGRAM tSET
%token tTYPE_INT tYPE_DOUBLE tTYPE_STRING tAT
%token tTYPE_VOID tEXTERNAL tTYPE_DOUBLE tNULLPTR
%token tFORWARD tPUBLIC tVAR tBLOCK tSTOP tWITH
%token tNEXT tRETURN tPRINTLN tAND tOR tFIND
%token tINDEX tOBJECTS tSIZEOF tFUNCTION tPRIVATE
%token tUNLESS tDO tFOR tAPPLY tDOTS tARROW tSWEEP tCHANGE

%type <block> block_content block
%type <sequence> exprs file global_declarations declarations instrs opt_args args opt_exprs
%type <expression> literal expr opt_global_init global_init fundef opt_init
%type <lvalue> lval
%type <type> fun_type data_type void_type void_pointer var_type return_type var
%type <types> var_types
%type <node> main declaration arg global_declaration instr
%nonassoc tIFX
%nonassoc tELSE

%left tGE tLE tEQ tNE '>' '<'
%left '+' '-'
%left '*' '/' '%'

%{
//-- The rules below will be included in yyparse, the main parsing function.
%}
%%

file : /* empty */                                { compiler->ast($$ = new cdk::sequence_node(LINE)); }
     | global_declarations                        { compiler->ast($$ = $1); }
     | main                                       { compiler->ast($$ = new cdk::sequence_node(LINE, $1)); }
     | global_declarations main                   { compiler->ast($$ = new cdk::sequence_node(LINE, $2, $1)); }
     ;

main : '(' tPROGRAM block_content ')'             { $$ = new til::function_definition_node(LINE, $3); }
     ;

global_declarations : global_declaration                              { $$ = new cdk::sequence_node(LINE, $1); }
                    | global_declarations global_declaration          { $$ = new cdk::sequence_node(LINE, $2, $1); }
                    ;

global_declaration : '(' tPUBLIC var_type tIDENTIFIER opt_global_init ')'         { $$ = new til::declaration_node(LINE, tPUBLIC, $3, *$4, $5); delete $4; }
                   | '(' tPUBLIC var tIDENTIFIER global_init ')'                  { $$ = new til::declaration_node(LINE, tPUBLIC, $3, *$4, $5); delete $4; }
                   | '(' tPUBLIC tIDENTIFIER global_init ')'                      { $$ = new til::declaration_node(LINE, tPUBLIC, nullptr, *$3, $4); delete $3; }
                   | '(' tFORWARD var_type tIDENTIFIER ')'                        { $$ = new til::declaration_node(LINE, tFORWARD, $3, *$4, nullptr); delete $4; }
                   | '(' tEXTERNAL fun_type tIDENTIFIER ')'                       { $$ = new til::declaration_node(LINE, tEXTERNAL, $3, *$4, nullptr); delete $4; }
                   | '(' var_type tIDENTIFIER opt_global_init ')'                 { $$ = new til::declaration_node(LINE, tPRIVATE, $2, *$3, $4); delete $3; }
                   | '(' var tIDENTIFIER global_init ')'                          { $$ = new til::declaration_node(LINE, tPRIVATE, $2, *$3, $4); delete $3; }
                   | '(' tIDENTIFIER global_init ')'                              { $$ = new til::declaration_node(LINE, tPRIVATE, nullptr, *$2, $3); delete $2; }
                   ;

opt_global_init : /* empty */             { $$ = nullptr; }
                | global_init             { $$ = $1; }
                ;

global_init : literal                     { $$ = $1; }
            | fundef                      { $$ = $1; }
            ;

opt_init : /* empty */                    { $$ = nullptr; }
         | expr                           { $$ = $1; }
         ;

var : tVAR                                { $$ = cdk::primitive_type::create(0, cdk::TYPE_UNSPEC); }
    ;

block : '(' tBLOCK block_content ')'                    { $$ = $3; }
      ;

block_content : declarations instrs                     { $$ = new til::block_node(LINE, $1, $2); }
               | declarations                           { $$ = new til::block_node(LINE, $1, nullptr); }
               | instrs                                 { $$ = new til::block_node(LINE, nullptr, $1); }
               | /* Empty block */                      { $$ = new til::block_node(LINE, nullptr, nullptr); }
                ;

declarations : declaration	                          { $$ = new cdk::sequence_node(LINE, $1); }
             | declarations declaration                 { $$ = new cdk::sequence_node(LINE, $2, $1); }
             ;

declaration : '(' var_type tIDENTIFIER opt_init ')'     { $$ = new til::declaration_node(LINE, tPRIVATE, $2, *$3, $4); delete $3; }
            | '(' var tIDENTIFIER expr ')'              { $$ = new til::declaration_node(LINE, tPRIVATE, $2, *$3, $4); delete $3; }
            ;

instrs : instr                               { $$ = new cdk::sequence_node(LINE, $1); }
       | instrs instr                        { $$ = new cdk::sequence_node(LINE, $2, $1); }
       ;

instr : block                                { $$ = $1; } 
      | expr                                 { $$ = new til::evaluation_node(LINE, $1); }
      | '(' tIF expr instr ')'               { $$ = new til::if_node(LINE, $3, $4); }
      | '(' tIF expr instr instr ')'         { $$ = new til::if_else_node(LINE, $3, $4, $5); }
      | '(' tLOOP expr instr ')'             { $$ = new til::loop_node(LINE, $3, $4); }
      | '(' tSTOP ')'                        { $$ = new til::stop_node(LINE); }
      | '(' tSTOP tINTEGER ')'               { $$ = new til::stop_node(LINE, $3); }
      | '(' tNEXT ')'                        { $$ = new til::next_node(LINE); }
      | '(' tNEXT tINTEGER ')'               { $$ = new til::next_node(LINE, $3); }
      | '(' tRETURN ')'                      { $$ = new til::return_node(LINE); }
      | '(' tRETURN expr ')'                 { $$ = new til::return_node(LINE, $3); }
      | '(' tPRINT exprs ')'                 { $$ = new til::print_node(LINE, $3, false); }
      | '(' tPRINTLN exprs ')'               { $$ = new til::print_node(LINE, $3, true); }
      | '(' tCHANGE expr tARROW expr tWITH expr tDOTS expr ')'               { $$ = new til::change_node(LINE, $3, $5, $7, $9); }
      | '(' tWITH expr expr expr expr ')'    { $$ = new til::with_node(LINE, $3, $4, $5, $6);}
      | '(' tUNLESS expr tFOR expr tDO expr tAPPLY expr ')'            { $$ = new til::unless_node(LINE, $3, $5, $7, $9);}
      | '(' tSWEEP expr tARROW expr tDOTS expr tWITH expr tIF expr ')' { $$ = new til::sweep_node(LINE, $3, $5, $7, $9, $11);}
      ;

opt_exprs : /* empty */                      { $$ = nullptr; }
          | exprs                            { $$ = $1; }
          ;

exprs : expr                                 { $$ = new cdk::sequence_node(LINE, $1); }
      | exprs expr                           { $$ = new cdk::sequence_node(LINE, $2, $1); }
      ;

expr :  literal                              { $$ = $1; }
     | '(' '-' expr ')'                      { $$ = new cdk::unary_minus_node(LINE, $3); }
     | '(' '+' expr ')'                      { $$ = new cdk::unary_plus_node(LINE, $3); }
     | '(' '+' expr expr ')'                 { $$ = new cdk::add_node(LINE, $3, $4); }
     | '(' '-' expr expr ')'                 { $$ = new cdk::sub_node(LINE, $3, $4); }
     | '(' tFIND lval ')'                    { $$ = new til::address_of_node(LINE, $3); }
     | '(' '*' expr expr ')'                 { $$ = new cdk::mul_node(LINE, $3, $4); }
     | '(' '/' expr expr ')'                 { $$ = new cdk::div_node(LINE, $3, $4); }
     | '(' '%' expr expr ')'                 { $$ = new cdk::mod_node(LINE, $3, $4); }
     | '(' '<' expr expr ')'                 { $$ = new cdk::lt_node(LINE, $3, $4); }
     | '(' '>' expr expr ')'                 { $$ = new cdk::gt_node(LINE, $3, $4); }
     | '(' tGE expr expr ')'                 { $$ = new cdk::ge_node(LINE, $3, $4); }
     | '(' tLE expr expr ')'                 { $$ = new cdk::le_node(LINE, $3, $4); }
     | '(' tNE expr expr ')'                 { $$ = new cdk::ne_node(LINE, $3, $4); }
     | '(' tEQ expr expr ')'                 { $$ = new cdk::eq_node(LINE, $3, $4); }
     | '(' '~' expr ')'                      { $$ = new cdk::not_node(LINE, $3); }
     | '(' tAND expr expr ')'                { $$ = new cdk::and_node(LINE, $3, $4); }
     | '(' tOR expr expr ')'                 { $$ = new cdk::or_node(LINE, $3, $4); }
     | '(' tREAD ')'                         { $$ = new til::read_node(LINE); }
     | '(' tSET lval expr ')'                { $$ = new cdk::assignment_node(LINE, $3, $4); }
     | '(' tOBJECTS expr ')'                 { $$ = new til::stack_alloc_node(LINE, $3); } // TODO check if correct
     | '(' tSIZEOF expr  ')'                 { $$ = new til::sizeof_node(LINE, $3); }
     | lval                                  { $$ = new cdk::rvalue_node(LINE, $1); }
     | fundef                                { $$ = $1; }
     | '(' tAT opt_exprs ')'                 { $$ = new til::function_call_node(LINE, nullptr, $3); }
     | '(' expr opt_exprs ')'                { $$ = new til::function_call_node(LINE, $2, $3); }
     ;

fundef : '(' tFUNCTION '(' return_type opt_args ')'  block_content ')' {
      $$ = new til::function_definition_node(LINE, $4, $5, $7);
      }
       ;

data_type : tTYPE_STRING                     { $$ = cdk::primitive_type::create(4, cdk::TYPE_STRING); }
          | tTYPE_INT                        { $$ = cdk::primitive_type::create(4, cdk::TYPE_INT); }
          | tTYPE_DOUBLE                     { $$ = cdk::primitive_type::create(8, cdk::TYPE_DOUBLE); }
          | fun_type                         { $$ = $1; }
          | data_type '!'                    { $$ = cdk::reference_type::create(4, $1); }
          ;

fun_type : '(' return_type '(' var_types ')' ')'     { $$ = cdk::functional_type::create(*$4, $2); delete $4; }
         | '(' return_type ')'                       { $$ = cdk::functional_type::create($2); }
         ;

return_type : var_type                       { $$ = $1; }
            | void_type                      { $$ = $1; }
            ;

opt_args : /* empty */                       { $$ = new cdk::sequence_node(LINE); }
         | args                              { $$ = $1; }
         ;

args : arg                                   { $$ = new cdk::sequence_node(LINE, $1); }
     | args arg                              { $$ = new cdk::sequence_node(LINE, $2, $1); }
     ;

arg : '(' var_type tIDENTIFIER ')'           { $$ = new til::declaration_node(LINE, tPRIVATE, $2, *$3, NULL); delete $3; }
    ;

var_types : var_type                         { $$ = new std::vector<std::shared_ptr<cdk::basic_type>>(); $$->push_back($1); }
           | var_types var_type              { $$ = $1; $$->push_back($2); }
           ;

var_type : data_type                         { $$ = $1; }
         | void_pointer                      { $$ = $1; }
         ;

void_pointer : void_pointer '!'              { $$ = cdk::reference_type::create(4, $1); }
             | void_type '!'                 { $$ = cdk::reference_type::create(4, $1); }
             ;

void_type : tTYPE_VOID                       { $$ = cdk::primitive_type::create(4, cdk::TYPE_VOID); }
          ;

literal : tINTEGER                           { $$ = new cdk::integer_node(LINE, $1); }
        | tDOUBLE                            { $$ = new cdk::double_node(LINE, $1); }
        | tSTRING                            { $$ = new cdk::string_node(LINE, $1); }
        | tNULLPTR                           { $$ = new til::nullptr_node(LINE); }
        ;

lval : tIDENTIFIER                           { $$ = new cdk::variable_node(LINE, $1); }
     | '(' tINDEX expr expr ')'              { $$ = new til::index_node(LINE, $3, $4); }
     ;

%%
