#ifndef __TIL_AST_WITH_NODE_H__
#define __TIL_AST_WITH_NODE_H__

#include <cdk/ast/expression_node.h>

namespace til {

  /**
   * Class for describing with nodes.
   */
  class with_node: public cdk::expression_node {
    cdk::expression_node *_function;
    cdk::expression_node *_vector;
    cdk::expression_node *_low;
    cdk::expression_node *_high;

  public:
    with_node(int lineno, cdk::expression_node *function, cdk::expression_node *vector,
              cdk::expression_node *low, cdk::expression_node *high) :
        cdk::expression_node(lineno), _function(function), _vector(vector),
        _low(low), _high(high) {
    }


    cdk::expression_node *function() const { return _function; }
    cdk::expression_node *vector() const { return _vector; }
    cdk::expression_node *low() const { return _low; }
    cdk::expression_node *high() const { return _high; }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_with_node(this, level);
    }

  };

} // namespace til

#endif
