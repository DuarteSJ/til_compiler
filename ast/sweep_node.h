#ifndef __TIL_AST_SWEEP_NODE_H__
#define __TIL_AST_SWEEP_NODE_H__

#include <cdk/ast/expression_node.h>

namespace til {

  /**
   * Class for describing function call nodes.
   */
  class sweep_node: public cdk::expression_node {
    cdk::expression_node *_vector;
    cdk::expression_node *_low;
    cdk::expression_node *_high;
    cdk::expression_node *_function;
    cdk::expression_node *_condition;

  public:
    sweep_node(int lineno, cdk::expression_node *vector, cdk::expression_node *low, cdk::expression_node *high,
                cdk::expression_node *function, cdk::expression_node *condition) :
        cdk::expression_node(lineno), _vector(vector), _low(low), _high(high), _function(function), _condition(condition) {
    }


    cdk::expression_node *vector() const { return _vector; }

    cdk::expression_node *low() const { return _low; }

    cdk::expression_node *high() const { return _high; }

    cdk::expression_node *function() const { return _function; }

    cdk::expression_node *condition() const { return _condition; }


    void accept(basic_ast_visitor *sp, int level) {
      sp->do_sweep_node(this, level);
    }

  };

} // namespace til

#endif
