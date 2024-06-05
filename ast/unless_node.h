#ifndef __TIL_AST_UNLESS_NODE_H__
#define __TIL_AST_UNLESS_NODE_H__

#include <cdk/ast/expression_node.h>

namespace til {

  /**
   * Class for describing unless nodes.
   */
  class unless_node : public cdk::basic_node {
    cdk::expression_node *_condition;
    cdk::expression_node *_pointer;
    cdk::expression_node *_value;
    cdk::expression_node *_function;

  public:
    unless_node(int lineno, cdk::expression_node *condition, cdk::expression_node *pointer,
                cdk::expression_node *value, cdk::expression_node *function) :
        cdk::basic_node(lineno), _condition(condition), _pointer(pointer),
        _value(value), _function(function) {
    }

    cdk::expression_node *condition() { return _condition; }

    cdk::expression_node *pointer() { return _pointer; }

    cdk::expression_node *value() { return _value; }

    cdk::expression_node *function() { return _function; }

    void accept(basic_ast_visitor *sp, int level) { sp->do_unless_node(this, level); }

  };

} // til

#endif
