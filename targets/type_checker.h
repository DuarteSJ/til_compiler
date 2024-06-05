#ifndef __TIL_TARGETS_TYPE_CHECKER_H__
#define __TIL_TARGETS_TYPE_CHECKER_H__

#include "targets/basic_ast_visitor.h"
#include ".auto/all_nodes.h"
namespace til {

  /**
   * Print nodes as XML elements to the output stream.
   */
  class type_checker: public basic_ast_visitor {
    cdk::symbol_table<til::symbol> &_symtab;

    basic_ast_visitor *_parent;

  public:
    type_checker(std::shared_ptr<cdk::compiler> compiler, cdk::symbol_table<til::symbol> &symtab, basic_ast_visitor *parent) :
        basic_ast_visitor(compiler), _symtab(symtab), _parent(parent) {
    }

  public:
    ~type_checker() {
      os().flush();
    }

  protected:
    bool do_check_compatible_ptr_types(std::shared_ptr<cdk::basic_type> type1,
                                   std::shared_ptr<cdk::basic_type> type2);
    bool do_check_compatible_func_types(std::shared_ptr<cdk::functional_type> type1,
                                    std::shared_ptr<cdk::functional_type> type2);
    bool do_check_compatible_types(std::shared_ptr<cdk::basic_type> type1,
                                  std::shared_ptr<cdk::basic_type> type2,
                                  bool is_return = false);
    void do_throw_incompatible_types(std::shared_ptr<cdk::basic_type> type1,
                                 std::shared_ptr<cdk::basic_type> type2,
                                 bool is_return = false);
    void do_change_type_on_match(cdk::typed_node *const lvalue,
                              cdk::typed_node *const rvalue);
    void do_UnaryExpression(cdk::unary_operation_node *const node, int lvl);
    bool do_BinaryExpression(cdk::binary_operation_node *const node, int lvl);
    void do_IBinaryExpression(cdk::binary_operation_node *const node, int lvl);
    void do_IDBinaryExpression(cdk::binary_operation_node *const node, int lvl);
    bool do_PIDBinaryExpression(cdk::binary_operation_node *const node, int lvl);
    bool do_LogicalBinaryExpression(cdk::binary_operation_node *const node, int lvl);
    void do_ComparisonBinaryExpression(cdk::binary_operation_node *const node, int lvl);
    void do_EqualityBinaryExpression(cdk::binary_operation_node *const node, int lvl);
    template<typename T>
    void process_literal(cdk::literal_node<T> *const node, int lvl) {
    }

  public:
    // do not edit these lines
#define __IN_VISITOR_HEADER__
#include ".auto/visitor_decls.h"       // automatically generated
#undef __IN_VISITOR_HEADER__
    // do not edit these lines: end

  };

} // til

//---------------------------------------------------------------------------
//     HELPER MACRO FOR TYPE CHECKING
//---------------------------------------------------------------------------

#define CHECK_TYPES(compiler, symtab, node) { \
  try { \
    til::type_checker checker(compiler, symtab, this); \
    (node)->accept(&checker, 0); \
  } \
  catch (const std::string &problem) { \
    std::cerr << (node)->lineno() << ": " << problem << std::endl; \
    return; \
  } \
}

#define ASSERT_SAFE_EXPRESSIONS CHECK_TYPES(_compiler, _symtab, node)

#endif
