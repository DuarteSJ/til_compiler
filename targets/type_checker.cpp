#include <string>
#include "targets/type_checker.h"
#include ".auto/all_nodes.h"  // automatically generated
#include <cdk/types/primitive_type.h>

#include <til_parser.tab.h>

#define ASSERT_UNSPEC { if (node->type() != nullptr && !node->is_typed(cdk::TYPE_UNSPEC)) return; }

//---------------------------------------------------------------------------

bool til::type_checker::do_check_compatible_ptr_types(
    std::shared_ptr<cdk::basic_type> type1, std::shared_ptr<cdk::basic_type> type2) {
  auto type1_ptr = type1;
  auto type2_ptr = type2;
  while (type1_ptr->name() == cdk::TYPE_POINTER &&
         type2_ptr->name() == cdk::TYPE_POINTER) {
    type1_ptr = cdk::reference_type::cast(type1_ptr)->referenced();
    type2_ptr = cdk::reference_type::cast(type2_ptr)->referenced();
  }
  return type1_ptr->name() == type2_ptr->name() || type2_ptr->name() == cdk::TYPE_UNSPEC;
}

bool til::type_checker::do_check_compatible_func_types(
    std::shared_ptr<cdk::functional_type> type1,
    std::shared_ptr<cdk::functional_type> type2) {

  // check for compatible return types
  if ((type1->output_length() > 0 && type2->output_length() > 0) &&
      !do_check_compatible_types(type1->output(0), type2->output(0)))
    return false;

  // check for same number of arguments
  if (type1->input_length() != type2->input_length())
    return false;

  // check for compatible argument types
  for (size_t i = 0; i < type1->input_length(); i++)
    if (!do_check_compatible_types(type1->input(i), type2->input(i)))
      return false;
  return true;
}

bool til::type_checker::do_check_compatible_types(
    std::shared_ptr<cdk::basic_type> type1, std::shared_ptr<cdk::basic_type> type2,
    bool is_return) {
  const auto t1_name = type1->name();
  const auto type2_name = type2->name();
  switch (t1_name) {
  case cdk::TYPE_INT:
  case cdk::TYPE_DOUBLE:
    if (!(type2_name == cdk::TYPE_DOUBLE || type2_name == cdk::TYPE_INT))
      return false;
    break;
  case cdk::TYPE_STRING:
    if (type2_name != cdk::TYPE_STRING)
      return false;
    break;
  case cdk::TYPE_POINTER:
    if (is_return == (type2_name == cdk::TYPE_POINTER) &&
        !do_check_compatible_ptr_types(type1, type2))
      return false;

    break;
  case cdk::TYPE_FUNCTIONAL:
    if (!((type2_name == cdk::TYPE_FUNCTIONAL &&
           do_check_compatible_func_types(cdk::functional_type::cast(type1),
                                      cdk::functional_type::cast(type2))) ||
          (type2_name == cdk::TYPE_POINTER &&
           cdk::reference_type::cast(type2)->referenced() == nullptr)))
      return false;
    break;
  case cdk::TYPE_UNSPEC: // useful for auto cases
    if (type2_name == cdk::TYPE_VOID)
      // auto x = f(), where f calls return void, is not allowed
      return false;
    break;
  default:
    if (t1_name != type2_name)
      return false;
  }
  return true;
}

void til::type_checker::do_throw_incompatible_types(
    std::shared_ptr<cdk::basic_type> type1, std::shared_ptr<cdk::basic_type> type2,
    bool is_return) {
  if (do_check_compatible_types(type1, type2))
    return;

  const std::string field_name =
      is_return ? "return" : "initialization";
  switch (type1->name()) {
  case cdk::TYPE_INT:
  case cdk::TYPE_DOUBLE:
    throw std::string("wrong type in " + field_name +
                      " (expected double or int)");
  case cdk::TYPE_STRING:
    throw std::string("wrong type in " + field_name + " (expected string)");
  case cdk::TYPE_POINTER:
    throw std::string("wrong type in " + field_name + " (expected pointer)");
  case cdk::TYPE_FUNCTIONAL:
    throw std::string("wrong type in " + field_name + " (expected function)");
  default:
    throw std::string("unknown type in " + field_name);
  }
}

void til::type_checker::do_change_type_on_match(cdk::typed_node *const lvalue,
                                             cdk::typed_node *const rvalue) {
  const auto ltype = lvalue->type();
  const auto rtype = rvalue->type();
  if (ltype->name() == cdk::TYPE_UNSPEC && rtype->name() == cdk::TYPE_UNSPEC) {
    // auto x = input;
    lvalue->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
    rvalue->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
  } else if ((ltype->name() == cdk::TYPE_POINTER &&
              rtype->name() == cdk::TYPE_POINTER &&
              do_check_compatible_ptr_types(ltype, rtype)) ||
             (ltype->name() == cdk::TYPE_FUNCTIONAL &&
              rtype->name() == cdk::TYPE_FUNCTIONAL &&
              do_check_compatible_func_types(cdk::functional_type::cast(ltype),
                                         cdk::functional_type::cast(rtype))) ||
             ((ltype->name() == cdk::TYPE_INT ||
               ltype->name() == cdk::TYPE_DOUBLE) &&
              rtype->name() == cdk::TYPE_UNSPEC)) {
    rvalue->type(ltype);
  }
}

void til::type_checker::do_UnaryExpression(
          cdk::unary_operation_node *const node, int lvl) {
  //TODO: check if this is correct. It probably is
  ASSERT_UNSPEC;
  node->argument()->accept(this, lvl + 2);
  if (!node->argument()->is_typed(cdk::TYPE_INT) &&
      !node->argument()->is_typed(cdk::TYPE_DOUBLE)) {
    throw std::string("wrong type in argument of unary expression");
  }
  node->type(node->argument()->type());
}

bool til::type_checker::do_BinaryExpression(
          cdk::binary_operation_node *const node, int lvl) {
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);

  if (node->left()->is_typed(cdk::TYPE_INT) ||
      node->left()->is_typed(cdk::TYPE_UNSPEC)) {
    if (node->right()->is_typed(cdk::TYPE_INT))
      node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
    else if (node->right()->is_typed(cdk::TYPE_DOUBLE))
      node->type(cdk::primitive_type::create(8, cdk::TYPE_DOUBLE));
    else if (node->right()->is_typed(cdk::TYPE_UNSPEC)) {
      node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
      node->left()->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
      node->right()->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
      // TODO: check if this is correct (two unspecs make an int?)
    } else {
      return false;
    }
  } else if (node->left()->is_typed(cdk::TYPE_DOUBLE)) {
      if (node->right()->is_typed(cdk::TYPE_DOUBLE) ||
          node->right()->is_typed(cdk::TYPE_INT))
        node->type(cdk::primitive_type::create(8, cdk::TYPE_DOUBLE));
      else if (node->right()->is_typed(cdk::TYPE_UNSPEC)) {
        node->type(cdk::primitive_type::create(8, cdk::TYPE_DOUBLE));
        node->right()->type(cdk::primitive_type::create(8, cdk::TYPE_DOUBLE));
      } else {
        return false;
      }
  } else {
    return false;
  }
  return true;
}

void til::type_checker::do_IBinaryExpression(
          cdk::binary_operation_node *const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (!node->left()->is_typed(cdk::TYPE_INT)){
    throw std::string("wrong type in left argument of binary expression");
  }
  node->right()->accept(this, lvl + 2);
  if (!node->right()->is_typed(cdk::TYPE_INT)){
    throw std::string("wrong type in right argument of binary expression");  
  }
}

void til::type_checker::do_IDBinaryExpression(
          cdk::binary_operation_node *const node, int lvl) {
  ASSERT_UNSPEC;
  if(!do_BinaryExpression(node, lvl)){
    throw std::string("wrong type in binary expression");
  }
}

bool til::type_checker::do_PIDBinaryExpression(
          cdk::binary_operation_node *const node, int lvl) {
  if(do_BinaryExpression(node, lvl)){
    return true;
  }
  else if(node->left()->is_typed(cdk::TYPE_POINTER) && node->right()->is_typed(cdk::TYPE_INT)){
    node->type(node->left()->type());
    return true;
  }
  else if(node->left()->is_typed(cdk::TYPE_INT) && node->right()->is_typed(cdk::TYPE_POINTER)){
    node->type(node->right()->type());
    return true;
  }
  else{
    return false;
  }
}

bool til::type_checker::do_LogicalBinaryExpression(
          cdk::binary_operation_node *const node, int lvl) {
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);

  if (node->left()->is_typed(cdk::TYPE_INT) ||
      node->left()->is_typed(cdk::TYPE_UNSPEC)) {
    if (node->right()->is_typed(cdk::TYPE_INT))
      node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
    else if (node->right()->is_typed(cdk::TYPE_UNSPEC)) {
      node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
      node->left()->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
      node->right()->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
      //TODO check if this is correct (two unspecs make an int?)
    } else {
      return false;
    }
  } else {
    return false;
  }
  return true;
}

void til::type_checker::do_ComparisonBinaryExpression(
    cdk::binary_operation_node *const node, int lvl) {
  do_IDBinaryExpression(node, lvl);
  node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
}

void til::type_checker::do_EqualityBinaryExpression(
    cdk::binary_operation_node *const node, int lvl) {
  //TODO: are accepts needed here?
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  if (do_BinaryExpression(node, lvl) ||
      do_check_compatible_ptr_types(node->left()->type(), node->right()->type())) {
    node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
  }
  else {
    throw std::string("wrong type in binary expression");
  }

}
//---------------------------------------------------------------------------

void til::type_checker::do_sequence_node(cdk::sequence_node *const node, int lvl) {
  for (auto n: node->nodes()) {
    n->accept(this, lvl);
  }
}

void til::type_checker::do_nil_node(cdk::nil_node *const node, int lvl) {
  // EMPTY
}

void til::type_checker::do_data_node(cdk::data_node *const node, int lvl) {
  // EMPTY
}

void til::type_checker::do_not_node(cdk::not_node *const node, int lvl) {
  ASSERT_UNSPEC;
  node->argument()->accept(this, lvl + 2);
  if (!node->argument()->is_typed(cdk::TYPE_INT)) {
    throw std::string("wrong type in argument of not expression");
  }
  node->type(node->argument()->type());
}

void til::type_checker::do_and_node(cdk::and_node *const node, int lvl) {
  do_LogicalBinaryExpression(node, lvl);
}

void til::type_checker::do_or_node(cdk::or_node *const node, int lvl) {
  do_LogicalBinaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void til::type_checker::do_integer_node(cdk::integer_node *const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
}

void til::type_checker::do_string_node(cdk::string_node *const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(cdk::primitive_type::create(4, cdk::TYPE_STRING));
}

void til::type_checker::do_double_node(cdk::double_node *const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(cdk::primitive_type::create(8, cdk::TYPE_DOUBLE));
}

//---------------------------------------------------------------------------

void til::type_checker::do_unary_minus_node(cdk::unary_minus_node *const node, int lvl) {
  do_UnaryExpression(node, lvl);
}

void til::type_checker::do_unary_plus_node(cdk::unary_plus_node *const node, int lvl) {
  do_UnaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void til::type_checker::do_add_node(cdk::add_node *const node, int lvl) {
  ASSERT_UNSPEC;
  if(!do_PIDBinaryExpression(node, lvl))
    throw std::string("wrong type in addition expression");
}

void til::type_checker::do_sub_node(cdk::sub_node *const node, int lvl) {
  ASSERT_UNSPEC;
  if(do_PIDBinaryExpression(node, lvl))
    return;
  // Case for pointer subtraction
  if(node->left()->is_typed(cdk::TYPE_POINTER) && node->right()->is_typed(cdk::TYPE_POINTER)){
    if (!do_check_compatible_ptr_types(node->left()->type(), node->right()->type())) {
      throw std::string("wrong type in subtraction expression");
    }
    node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
  }
}

void til::type_checker::do_mul_node(cdk::mul_node *const node, int lvl) {
  do_IDBinaryExpression(node, lvl);
}

void til::type_checker::do_div_node(cdk::div_node *const node, int lvl) {
  do_IDBinaryExpression(node, lvl);
}

void til::type_checker::do_mod_node(cdk::mod_node *const node, int lvl) {
  do_IDBinaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void til::type_checker::do_lt_node(cdk::lt_node *const node, int lvl) {
  do_ComparisonBinaryExpression(node, lvl);
}

void til::type_checker::do_le_node(cdk::le_node *const node, int lvl) {
  do_ComparisonBinaryExpression(node, lvl);
}

void til::type_checker::do_ge_node(cdk::ge_node *const node, int lvl) {
  do_ComparisonBinaryExpression(node, lvl);
}

void til::type_checker::do_gt_node(cdk::gt_node *const node, int lvl) {
  do_ComparisonBinaryExpression(node, lvl);
}

void til::type_checker::do_ne_node(cdk::ne_node *const node, int lvl) {
  do_EqualityBinaryExpression(node, lvl);
}

void til::type_checker::do_eq_node(cdk::eq_node *const node, int lvl) {
  do_EqualityBinaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void til::type_checker::do_variable_node(cdk::variable_node *const node, int lvl) {
  ASSERT_UNSPEC;
  const std::string &id = node->name();
  std::shared_ptr<til::symbol> symbol = _symtab.find(id);

  if (symbol != nullptr) {
    node->type(symbol->type());
  } else {
    throw id;
  }
}

void til::type_checker::do_rvalue_node(cdk::rvalue_node *const node, int lvl) {
  ASSERT_UNSPEC;
  try {
    node->lvalue()->accept(this, lvl);
    node->type(node->lvalue()->type());
  } catch (const std::string &id) {
    throw "undeclared variable '" + id + "'";
  }
}

void til::type_checker::do_assignment_node(cdk::assignment_node *const node, int lvl) {
  ASSERT_UNSPEC;
  node->lvalue()->accept(this, lvl + 2);
  node->rvalue()->accept(this, lvl + 2);

  do_change_type_on_match(node->lvalue(), node->rvalue());
  const auto lval_type = node->lvalue()->type();
  const auto rval_type = node->rvalue()->type();
  do_throw_incompatible_types(lval_type, rval_type);
  node->type(lval_type);
}

void til::type_checker::do_evaluation_node(til::evaluation_node *const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
}

void til::type_checker::do_print_node(til::print_node *const node, int lvl) {
  node->arguments()->accept(this, lvl + 2);
  for (auto *node : node->arguments()->nodes()) {
    const auto &type = (dynamic_cast<cdk::expression_node *>(node))->type();
    if (!(type->name() == cdk::TYPE_INT) &&
        !(type->name() == cdk::TYPE_DOUBLE) &&
        !(type->name() == cdk::TYPE_STRING)) {
      throw std::string("wrong type in argument of print expression");
    }
  }
}

//---------------------------------------------------------------------------

void til::type_checker::do_read_node(til::read_node *const node, int lvl) {
  //TODO: maybe change this
  ASSERT_UNSPEC;
  node->type(cdk::primitive_type::create(0, cdk::TYPE_UNSPEC));
}

//---------------------------------------------------------------------------

void til::type_checker::do_loop_node(til::loop_node *const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

//---------------------------------------------------------------------------

void til::type_checker::do_if_node(til::if_node *const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
  node->block()->accept(this, lvl + 4);
}

void til::type_checker::do_if_else_node(til::if_else_node *const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
  node->thenblock()->accept(this, lvl + 4);
  node->elseblock()->accept(this, lvl + 4);
}

//---------------------------------------------------------------------------

void til::type_checker::do_block_node(til::block_node *const node, int lvl) {
  // Empty
}

//---------------------------------------------------------------------------

void til::type_checker::do_stop_node(til::stop_node *const node, int lvl) {
  // Empty
}

//---------------------------------------------------------------------------

void til::type_checker::do_next_node(til::next_node *const node, int lvl) {
  // Empty
}

//---------------------------------------------------------------------------

void til::type_checker::do_return_node(til::return_node *const node, int lvl) {
  const auto function = _symtab.find("@");
  const auto ret_val = node->value();
  if (!function) { // we may be in main
    const auto main = _symtab.find("_main");
    if (main) {
      if (!ret_val)
        throw std::string("wrong type of return value in main (int expected)");
      ret_val->accept(this, lvl + 2);
      if (!ret_val->is_typed(cdk::TYPE_INT))
        throw std::string("wrong type of return value in main (int expected)");
      return;
    }
    throw std::string("return statement found outside function");
  } else if (!ret_val) {
    return;
  }

  const auto &fun_sym_type = cdk::functional_type::cast(function->type());
  const auto function_output = fun_sym_type->output(0);
  const bool has_output = fun_sym_type->output() != nullptr;
  if (has_output && function_output->name() == cdk::TYPE_VOID)
    throw std::string("return with a value in void function");
  else if (!has_output)
    throw std::string("unknown return type in function");

  ret_val->accept(this, lvl + 2);
  do_throw_incompatible_types(function_output, ret_val->type(), true);
}

//---------------------------------------------------------------------------

void til::type_checker::do_index_node(til::index_node *const node, int lvl) {
  ASSERT_UNSPEC;
  node->base()->accept(this, lvl + 2);
  if (!node->base()->is_typed(cdk::TYPE_POINTER)) {
    throw std::string("wrong type in base of index expression");
  }
  node->index()->accept(this, lvl + 2);
  if (!node->index()->is_typed(cdk::TYPE_INT)) {
    throw std::string("wrong type in index of index expression");
  }
  node->type(cdk::reference_type::cast(node->base()->type())->referenced());
}

//---------------------------------------------------------------------------

void til::type_checker::do_address_of_node(til::address_of_node *const node, int lvl) {
  ASSERT_UNSPEC;
  node->argument()->accept(this, lvl + 2);
  node->type(cdk::reference_type::create(4, node->argument()->type()));
}

//---------------------------------------------------------------------------

void til::type_checker::do_sizeof_node(til::sizeof_node *const node, int lvl) {
  ASSERT_UNSPEC;
  node->argument()->accept(this, lvl + 2);
  node->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
}

//---------------------------------------------------------------------------

void til::type_checker::do_function_definition_node(til::function_definition_node *const node, int lvl) {
  // empty
}

//---------------------------------------------------------------------------

void til::type_checker::do_function_call_node(til::function_call_node *const node, int lvl) {
  ASSERT_UNSPEC;
  std::vector<std::shared_ptr<cdk::basic_type>> args_types;

  if (node->function()) { // regular call
    node->function()->accept(this, lvl + 2);
    if (!(node->function()->is_typed(cdk::TYPE_FUNCTIONAL)))
      throw std::string("wrong type in function call expression");

    const auto &type = node->function()->type();
    args_types = cdk::functional_type::cast(type)->input()->components();
    node->type(cdk::functional_type::cast(type)->output(0));
  } else { // recursive call with "@""
    auto symbol = _symtab.find("@");
    if (!symbol) {
      throw std::string("recursive call not allowed in the current scope");
    }
    const auto &type = symbol->type();
    args_types = cdk::functional_type::cast(type)->input()->components();
    node->type(cdk::functional_type::cast(type)->output(0));
  }

  if (node->arguments()) {
    if (args_types.size() != node->arguments()->size())
      throw std::string(
          "wrong number of arguments in function call expression");
    node->arguments()->accept(this, lvl + 2);

    for (size_t i = 0; i < args_types.size(); i++) {
      const auto &param_type =
          dynamic_cast<cdk::expression_node *>(node->arguments()->node(i))
              ->type();
      // note that the second condition is to allow passing an int as a double
      if ((args_types[i] == param_type) ||
          (args_types[i]->name() == cdk::TYPE_DOUBLE &&
           param_type->name() == cdk::TYPE_INT))
        continue;
      throw std::string("wrong type in argument of function call expression");
    }
  }
}

//---------------------------------------------------------------------------

void til::type_checker::do_declaration_node(til::declaration_node *const node, int lvl) {
  const auto &init = node->init();
  if (init) {
    init->accept(this, lvl + 2);
    if (node->type()) {
      do_change_type_on_match(node, init);
      do_throw_incompatible_types(node->type(), init->type());
      if (node->type()->name() == cdk::TYPE_UNSPEC)
        node->type(init->type());
    } else {
      node->type(init->type());
    }
  }

  const auto new_symbol = til::make_symbol(
      node->type(), node->identifier(), (bool)node->init(), node->qualifier());
  if (!_symtab.insert(node->identifier(), new_symbol)) {
    // in this case, we are redeclaring a variable
    const auto previous_symbol = _symtab.find_local(node->identifier());
    // the redeclared type must be the exact same
    if (previous_symbol->type()->name() != node->type()->name())
      throw std::string("cannot redeclare variable '" + node->identifier() +
                        "' with incompatible type");
    _symtab.replace(node->identifier(), new_symbol);
  }
  _parent->set_new_symbol(new_symbol);
}

//---------------------------------------------------------------------------

void til::type_checker::do_stack_alloc_node(til::stack_alloc_node *const node, int lvl) {
  ASSERT_UNSPEC;
  node->argument()->accept(this, lvl + 2);
  if (!node->argument()->is_typed(cdk::TYPE_INT))
    throw std::string("wrong type in argument of stack_alloc expression");
  node->type(cdk::reference_type::create(
      4, cdk::primitive_type::create(0, cdk::TYPE_UNSPEC)));
}

//---------------------------------------------------------------------------

void til::type_checker::do_nullptr_node(til::nullptr_node *const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(cdk::reference_type::create(
      4, cdk::primitive_type::create(0, cdk::TYPE_VOID)));
}

//----------------------------------------------------------------------------

void til::type_checker::do_with_node(til::with_node *const node, int lvl) {
  node->function()->accept(this, lvl + 2);
  node->vector()->accept(this, lvl + 2);
  node->low()->accept(this, lvl + 2);
  node->high()->accept(this, lvl + 2);

  if(!node->vector()->is_typed(cdk::TYPE_POINTER)){
    throw std::string("wrong type in with statement (expected pointer)");
  }

  if(!node->function()->is_typed(cdk::TYPE_FUNCTIONAL)){
    throw std::string("wrong type in with statement (expected function)");
  }

  if(node->high()->is_typed(cdk::TYPE_UNSPEC)){
    node->high()->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
  }

  if(node->low()->is_typed(cdk::TYPE_UNSPEC)){
    node->low()->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
  }

  auto func = cdk::functional_type::cast(node->function()->type());

  if(!node->low()->is_typed(cdk::TYPE_INT) || !node->high()->is_typed(cdk::TYPE_INT)){
    throw std::string("wrong type in with statement (expected integer)");
  }

  if(func->input_length() != 1){
    throw std::string("wrong number of arguments in with statement");
  }
  auto ref = cdk::reference_type::cast(node->vector()->type());
  if(!do_check_compatible_types(func->input(0), ref->referenced(), true)){
    throw std::string("wrong type in with statement (expected vector)");
  }

}

void til::type_checker::do_unless_node(til::unless_node *const node, int lvl){
  node->value()->accept(this, lvl+2);

  if (node->value()->is_typed(cdk::TYPE_UNSPEC)){
    node->value()->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
  }

  if(!node->value()->is_typed(cdk::TYPE_INT))
    throw std::string("wrong type in value (expected int)");

  node->pointer()->accept(this, lvl+2);

  node->function()->accept(this, lvl+2);

  if (!(node->function()->is_typed(cdk::TYPE_FUNCTIONAL)))
      throw std::string("wrong type in function call expression");

  auto func = cdk::functional_type::cast(node->function()->type());
  auto ref = cdk::reference_type::cast(node->pointer()->type());

  if(func->input_length() != 1){
    throw std::string("wrong number of arguments in with statement");
  }

  do_throw_incompatible_types(func->input(0), ref->referenced());
  
  
  node->condition()->accept(this, lvl+2);

}

void til::type_checker::do_sweep_node(til::sweep_node *const node, int lvl){
  ASSERT_UNSPEC;
  node->low()->accept(this, lvl+2);
  if(node->low()->is_typed(cdk::TYPE_UNSPEC)){
    node->low()->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
  }
  if(!(node->low()->is_typed(cdk::TYPE_INT))){
    throw std::string("wrong type in low (expected int)");
  }
  node->high()->accept(this, lvl+2);
  if(node->high()->is_typed(cdk::TYPE_UNSPEC)){
    node->high()->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
  }
  if(!(node->high()->is_typed(cdk::TYPE_INT))){
    throw std::string("wrong type in high (expected int)");
  }
  
  node->function()->accept(this, lvl+2);
  auto func = cdk::functional_type::cast(node->function()->type());
  if(!node->function()->is_typed(cdk::TYPE_FUNCTIONAL)){
    throw std::string("wrong type in function (expected functional type)");
  }

  if(func->input_length() != 1){
    throw std::string("too many arguments in function");
  }

  node->vector()->accept(this, lvl+2);
  auto ref = cdk::reference_type::cast(node->vector()->type());

  do_throw_incompatible_types(func->input(0), ref->referenced());

  node->condition()->accept(this, lvl+2);
}

void til::type_checker::do_change_node(til::change_node *const node, int lvl) {
  node->low()->accept(this, lvl+2);
  if(node->low()->is_typed(cdk::TYPE_UNSPEC)){
    node->low()->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
  }

  if(!node->low()->is_typed(cdk::TYPE_INT)){
    throw std::string("Unespected type for loe (expected int)");
  }

  node->high()->accept(this, lvl+2);
  if(node->high()->is_typed(cdk::TYPE_UNSPEC)){
    node->high()->type(cdk::primitive_type::create(4, cdk::TYPE_INT));
  }

  if(!node->high()->is_typed(cdk::TYPE_INT)){
    throw std::string("Unespected type for loe (expected int)");
  }


  node->function()->accept(this, lvl+2);
  if(!node->function()->is_typed(cdk::TYPE_FUNCTIONAL)){
    throw std::string("Unexpected type for loe (expected int)");
  }

  auto func = cdk::functional_type::cast(node->function()->type()); 
  node->vector()->accept(this, lvl+2);
  if(!node->vector()->is_typed(cdk::TYPE_POINTER))
    throw std::string("Unexpected type for loe (expected int)");


  auto ref = cdk::reference_type::cast(node->vector()->type());

  do_throw_incompatible_types(func->input(0), ref->referenced());


}