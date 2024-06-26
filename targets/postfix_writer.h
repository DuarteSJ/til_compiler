#ifndef __TIL_TARGETS_POSTFIX_WRITER_H__
#define __TIL_TARGETS_POSTFIX_WRITER_H__

#include "targets/basic_ast_visitor.h"

#include <sstream>
#include <set>
#include <cdk/emitters/basic_postfix_emitter.h>

namespace til {

  //!
  //! Traverse syntax tree and generate the corresponding assembly code.
  //!
  class postfix_writer: public basic_ast_visitor {
    cdk::symbol_table<til::symbol> &_symtab;
    cdk::basic_postfix_emitter &_pf;

    int _lbl;
    int _offset = 0; //fp offset
    
    bool _inFuncBody = false;
    bool _inFuncArgs = false;
    bool _lastBlockInstrSeen = false;
    bool _mainReturnSeen = false;

    std::set<std::string> _functionsToDeclare;
    std::set<std::string> _symbolsToDeclare;

    std::string _currentForwardLabel;
    std::vector<std::string> _functionLabels;
    std::vector<std::shared_ptr<til::symbol>> _functions;

    //loop labels
    std::string _loopCond, _loopEnd;

  public:
    postfix_writer(std::shared_ptr<cdk::compiler> compiler, cdk::symbol_table<til::symbol> &symtab,
                   cdk::basic_postfix_emitter &pf) :
        basic_ast_visitor(compiler), _symtab(symtab), _pf(pf), _lbl(0) {
    }

  public:
    ~postfix_writer() {
      os().flush();
    }

  private:
    /** Method used to generate sequential labels. */
    inline std::string mklbl(int lbl) {
      std::ostringstream oss;
      if (lbl < 0)
        oss << ".L" << -lbl;
      else
        oss << "_L" << lbl;
      return oss.str();
    }

    void error(int lineno, std::string e) {
      std::cerr << lineno << ": " << e << std::endl;
    }
  
  protected:
    void do_PIDBinaryExpression(
      cdk::binary_operation_node *const node, int lvl
    );
    void do_GeneralLogicalBinaryExpression(
      cdk::binary_operation_node *const node, int lvl
    );

    void do_LocalVarInit(
      std::shared_ptr<til::symbol> symbol,
      cdk::expression_node *const initializer, int lvl
    );

    void do_GlobalVarInit(
      std::shared_ptr<til::symbol> symbol,
      cdk::expression_node *const initializer, int lvl
    );

    void do_MainFunction(
      til::function_definition_node *const node, int lvl
    );

    void do_NonMainFunction(
      til::function_definition_node *const node, int lvl
    );


  public:
  // do not edit these lines
#define __IN_VISITOR_HEADER__
#include ".auto/visitor_decls.h"       // automatically generated
#undef __IN_VISITOR_HEADER__
  // do not edit these lines: end

  };

} // til

#endif
