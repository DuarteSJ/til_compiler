#ifndef __TIL_AST_DECLARATION_NODE_H__
#define __TIL_AST_DECLARATION_NODE_H__

#include <cdk/ast/expression_node.h>
#include <cdk/ast/typed_node.h>
#include <string>

namespace til{
  /**
   * Class for describing function declaration nodes.
   */
  class declaration_node: public cdk::typed_node {
     int _qualifier;
     std::string _identifier;
     cdk::expression_node *_init;

  public:
    declaration_node(int lineno, int qualifier, std::shared_ptr<cdk::basic_type> type,
                              const std::string &identifier, cdk::expression_node *init) :
        cdk::typed_node(lineno), _qualifier(qualifier), _identifier(identifier), _init(init) {
      cdk::typed_node::type(type);
    }

    int qualifier() const { return _qualifier; }
    std::string identifier() const { return _identifier; }
    cdk::expression_node *init() const { return _init; }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_declaration_node(this, level);
    }
  };

} // namespace til

#endif
