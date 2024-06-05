#ifndef __TIL_AST_CHANGE_NODE_H__
#define __TIL_AST_CHANGE_NODE_H__

#include <cdk/ast/expression_node.h>

namespace til {

  /**
   * Class for describing block nodes.
   */
  class change_node: public cdk::basic_node {
    cdk::expression_node *_vector;
    cdk::expression_node *_function;
    cdk::expression_node *_low;
    cdk::expression_node *_high;

  public:
    change_node(int lineno, cdk::expression_node *vector, cdk::expression_node *function,
                cdk::expression_node *low, cdk::expression_node *high) :
        cdk::basic_node(lineno), _vector(vector), _function(function), _low(low), _high(high){
    }

    cdk::expression_node *vector() { return _vector; }
    cdk::expression_node *function() { return _function; }
    cdk::expression_node *low() { return _low; }
    cdk::expression_node *high() { return _high; }


    void accept(basic_ast_visitor *sp, int level) { sp->do_change_node(this, level); }

  };

} // til

#endif
