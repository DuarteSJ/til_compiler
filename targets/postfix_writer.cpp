#include <string>
#include <sstream>
#include "targets/type_checker.h"
#include "targets/postfix_writer.h"
#include ".auto/all_nodes.h"  // all_nodes.h is automatically generated
#include "targets/frame_size_calculator.h"

#include "til_parser.tab.h"

//---------------------------------------------------------------------------

void til::postfix_writer::do_PIDBinaryExpression(
    cdk::binary_operation_node *const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl + 2);
  if (node->is_typed(cdk::TYPE_DOUBLE) &&
      !node->left()->is_typed(cdk::TYPE_DOUBLE))
    _pf.I2D();
  else if (node->is_typed(cdk::TYPE_POINTER) &&
           !node->left()->is_typed(cdk::TYPE_POINTER)) {
    // type_checker already garanties that left is an integer
    // and right is a pointer
    const auto ref_right =
        cdk::reference_type::cast(node->right()->type())->referenced();
    _pf.INT(std::max(
        1, static_cast<int>(ref_right->size()))); // garanties that size is 1 for void
    _pf.MUL();
  }

  node->right()->accept(this, lvl + 2);
  if (node->is_typed(cdk::TYPE_DOUBLE) &&
      !node->right()->is_typed(cdk::TYPE_DOUBLE))
    _pf.I2D();
  else if (node->is_typed(cdk::TYPE_POINTER) &&
           !node->right()->is_typed(cdk::TYPE_POINTER)) {
    const auto ref_left =
        cdk::reference_type::cast(node->left()->type())->referenced();
    _pf.INT(std::max(
        1, static_cast<int>(ref_left->size()))); // void size should be 1 when
                                                 // doing pointer arithmetic
    _pf.MUL();
  }
}

void til::postfix_writer::do_GeneralLogicalBinaryExpression(
    cdk::binary_operation_node *const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl + 2);
  if (!node->left()->is_typed(cdk::TYPE_DOUBLE) &&
      node->right()->is_typed(cdk::TYPE_DOUBLE))
    _pf.I2D(); // convert left to double to match right

  node->right()->accept(this, lvl + 2);
  if (!node->right()->is_typed(cdk::TYPE_DOUBLE) &&
      node->left()->is_typed(cdk::TYPE_DOUBLE))
    _pf.I2D(); // convert right to double to match left

  if (node->left()->is_typed(cdk::TYPE_DOUBLE) ||
      node->right()->is_typed(cdk::TYPE_DOUBLE)) {
    // this is done so that we always
    // have 2 integer values on the stack 
    // at the end of this function
    _pf.DCMP();
    _pf.INT(0);
  }
}

void til::postfix_writer::do_LocalVarInit(
    std::shared_ptr<til::symbol> symbol,
    cdk::expression_node *const initializer, int lvl) {
  initializer->accept(this, lvl);
  switch (symbol->type()->name()) {
  case cdk::TYPE_INT:
  case cdk::TYPE_STRING:
  case cdk::TYPE_POINTER:
  case cdk::TYPE_FUNCTIONAL:
  case cdk::TYPE_UNSPEC: // cases such as `auto x = input;`
    _pf.LOCAL(symbol->offset());
    _pf.STINT();
    break;
  case cdk::TYPE_DOUBLE:
    if (initializer->is_typed(cdk::TYPE_INT))
      _pf.I2D();
    _pf.LOCAL(symbol->offset());
    _pf.STDOUBLE();
    break;
  default:
    error(initializer->lineno(), "invalid type for variable initialization");
  }
}

void til::postfix_writer::do_GlobalVarInit(
    std::shared_ptr<til::symbol> symbol,
    cdk::expression_node *const initializer, int lvl) {
  //TODO: check if this is correct
  switch (symbol->type()->name()) {
  case cdk::TYPE_INT:
  case cdk::TYPE_STRING:
  case cdk::TYPE_POINTER:
    _pf.DATA(); // Data segment, for global variables
    _pf.ALIGN();
    _pf.LABEL(symbol->name());
    initializer->accept(this, lvl + 2);
    break;
  case cdk::TYPE_DOUBLE:
    _pf.DATA(); // Data segment, for global variables
    _pf.ALIGN();
    _pf.LABEL(symbol->name());

    // the following initializations need to be done outside of the switch
    const cdk::integer_node *dclini;
    cdk::double_node *ddi;
    switch (initializer->type()->name()) {
    case cdk::TYPE_INT:
      // here, we actually want to initialize the variable with a double
      // thus, we need to convert the expression to a double node
      // NOTE: I don't like these variable names either, taken from DM
      dclini = dynamic_cast<const cdk::integer_node *>(initializer);
      ddi = new cdk::double_node(dclini->lineno(), dclini->value());
      ddi->accept(this, lvl + 2);
      break;
    case cdk::TYPE_DOUBLE:
      initializer->accept(this, lvl + 2);
      break;
    default:
      error(initializer->lineno(),
            "invalid type for double variable initialization");
    }
    break;
  case cdk::TYPE_FUNCTIONAL:
    _functions.push_back(symbol);
    initializer->accept(this, lvl);
    _pf.DATA(); // Data segment, for global variables
    _pf.ALIGN();
    if (symbol->qualifier() == tPUBLIC)
      _pf.GLOBAL(symbol->name(), _pf.OBJ());
    _pf.LABEL(symbol->name());
    _pf.SADDR(_functionLabels.back());
    break;
  default:
    error(initializer->lineno(), "invalid type for variable initialization");
  }
}

void til::postfix_writer::do_MainFunction(
    til::function_definition_node *const node, int lvl) {
  for (auto s_name : _symbolsToDeclare) {
    const auto symbol = _symtab.find(s_name);
    if (symbol->qualifier() == tEXTERNAL) {
      _functionsToDeclare.insert(s_name);
      continue;
    }

    _pf.BSS();
    _pf.ALIGN();
    _pf.LABEL(s_name);
    _pf.SALLOC(symbol->type()->size());
  }

  // Note that it's ok to name the function _main, as no variable may have
  // underscores
  const auto main =
      til::make_symbol(cdk::functional_type::create(
                           cdk::primitive_type::create(4, cdk::TYPE_INT)),
                       "_main", 0, tPRIVATE);
  _symtab.insert(main->name(), main);
  _functions.push_back(main);
  _functionLabels.push_back("_main");

  // generate the main function itself
  _symtab.push(); // entering new context
  _pf.TEXT("_main");
  _pf.ALIGN();
  _pf.GLOBAL("_main", _pf.FUNC());
  _pf.LABEL("_main");

  // compute stack size to be reserved for local variables
  frame_size_calculator fsc(_compiler, _symtab);
  node->accept(&fsc, lvl);
  _pf.ENTER(fsc.localsize());

  _inFuncBody = true;
  node->block()->accept(this, lvl + 2);
  _inFuncBody = false;

  _symtab.pop(); // leaving context

  _functionLabels.pop_back();
  _functions.pop_back();
  if (!_mainReturnSeen) {
    _pf.INT(0);
    _pf.STFVAL32();
  }
  _pf.LEAVE();
  _pf.RET();

  for (auto forwarded_function : _functionsToDeclare)
    _pf.EXTERN(forwarded_function);}

void til::postfix_writer::do_NonMainFunction(
    til::function_definition_node *const node, int lvl) {
  _symtab.push(); // args scope
  auto function = til::make_symbol(node->type(), "@", 0, tPRIVATE);
  if (_symtab.find_local(function->name())) {
    _symtab.replace(function->name(), function);
  } else {
    _symtab.insert(function->name(), function);
  }
  _functions.push_back(function);

  const auto functionLabel = mklbl(++_lbl);
  _functionLabels.push_back(functionLabel);

  const auto previous_offset = _offset;
  _offset =
      8; // prepare for arguments (4: remember to account for return address)

  if (node->arguments()) {
    _inFuncArgs = true;
    for (size_t ix = 0; ix < node->arguments()->size(); ix++) {
      node->arguments()->node(ix)->accept(this, lvl);
    }
    _inFuncArgs = false;
  }

  _pf.TEXT(functionLabel);
  _pf.ALIGN();
  _pf.LABEL(functionLabel);

  // compute stack size to be reserved for local variables
  frame_size_calculator fsc(_compiler, _symtab);
  node->accept(&fsc, lvl);
  _pf.ENTER(fsc.localsize());

  _offset = 0; // reset offset, prepare for local variables
  auto _previouslyInFunctionBody = _inFuncBody;
  _inFuncBody = true;
  if (node->block())
    node->block()->accept(this, lvl + 2);
  _inFuncBody = _previouslyInFunctionBody;
  _symtab.pop(); // leaving args scope
  _offset = previous_offset;

  if (function)
    _functions.pop_back();

  _pf.LEAVE();
  _pf.RET();

  if (_inFuncBody) {
    _functionLabels.pop_back();
    _pf.TEXT(_functionLabels.back());
    _pf.ADDR(functionLabel);
  }
}

//---------------------------------------------------------------------------

void til::postfix_writer::do_nil_node(cdk::nil_node * const node, int lvl) {
  // EMPTY
}

void til::postfix_writer::do_data_node(cdk::data_node * const node, int lvl) {
  // EMPTY
}

void til::postfix_writer::do_not_node(cdk::not_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS
  node->argument()->accept(this, lvl); // determine the value
  _pf.INT(0); // push a 0 to the stack (false)
  _pf.EQ(); // compare the two values
}

void til::postfix_writer::do_and_node(cdk::and_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  const auto lbl = mklbl(++_lbl); // generate a unique label
  node->left()->accept(this, lvl + 2); // determine the value of the left expression
  _pf.DUP32(); // duplicate the value at the top of the stack
  _pf.JZ(lbl); // if it is 0 (false), skip the right value
  node->right()->accept(this, lvl + 2); // else determine the value of the right expression
  _pf.AND(); // compute the logical and between the two values
  _pf.ALIGN();
  _pf.LABEL(lbl); // the label for the end of the and
}

void til::postfix_writer::do_or_node(cdk::or_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  const auto lbl = mklbl(++_lbl); // generate a unique label
  node->left()->accept(this, lvl + 2); // determine the value of the left expression
  _pf.DUP32(); // duplicate the value at the top of the stack
  _pf.JNZ(lbl); // if it is not 0 (true), skip the right value
  node->right()->accept(this, lvl + 2); // else determine the value of the right expression
  _pf.OR(); // compute the logical or between the two values
  _pf.ALIGN();
  _pf.LABEL(lbl); // the label for the end of the or
}

//---------------------------------------------------------------------------

void til::postfix_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  _lastBlockInstrSeen = false;
  for (size_t i = 0; i < node->size(); i++) {
    if (_lastBlockInstrSeen) {
      error(node->lineno(), "unreachable code");
      _lastBlockInstrSeen = false;
      return;
    }
    node->node(i)->accept(this, lvl);
  }
  _lastBlockInstrSeen = false;
}

//---------------------------------------------------------------------------

void til::postfix_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  if(_inFuncBody)
    _pf.INT(node->value());
  else
    _pf.SINT(node->value());
}

void til::postfix_writer::do_double_node(cdk::double_node * const node, int lvl) {
  if(_inFuncBody)
    _pf.DOUBLE(node->value());
  else
    _pf.SDOUBLE(node->value());
}

void til::postfix_writer::do_string_node(cdk::string_node * const node, int lvl) {
  int lbl1;

  /* generate the string */
  _pf.RODATA(); // strings are DATA readonly
  _pf.ALIGN(); // make sure we are aligned
  _pf.LABEL(mklbl(lbl1 = ++_lbl)); // give the string a name
  _pf.SSTRING(node->value()); // output string characters

  if(_inFuncBody){
    _pf.TEXT(_functionLabels.back()); // return to the TEXT segment
    _pf.ADDR(mklbl(lbl1)); // leave the address on the stack
  }
  else{
    _pf.DATA(); // return to the DATA segment
    _pf.SADDR(mklbl(lbl1)); // leave the address on the stack
  }
}

//---------------------------------------------------------------------------

void til::postfix_writer::do_unary_minus_node(cdk::unary_minus_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl + 2); // determine the value
  _pf.NEG(); // 2-complement
}

void til::postfix_writer::do_unary_plus_node(cdk::unary_plus_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl + 2); // determine the value
}

//---------------------------------------------------------------------------

void til::postfix_writer::do_add_node(cdk::add_node * const node, int lvl) {
  do_PIDBinaryExpression(node, lvl);
  if (node->is_typed(cdk::TYPE_DOUBLE))
    _pf.DADD();
  else
    _pf.ADD();
}

void til::postfix_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  //TODO: check if this is correct
  do_PIDBinaryExpression(node, lvl);
  if (node->is_typed(cdk::TYPE_DOUBLE)) {
    _pf.DSUB();
  } else {
    _pf.SUB();
    // special case for poiter subtraction
    if ((node->left()->is_typed(cdk::TYPE_POINTER) &&
         node->right()->is_typed(cdk::TYPE_POINTER)) &&
         cdk::reference_type::cast(node->left()->type())->referenced()->name() != cdk::TYPE_VOID) {
      _pf.INT(cdk::reference_type::cast(node->left()->type())
              ->referenced()->size());
      _pf.DIV();
    }
  }
}

void til::postfix_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  do_PIDBinaryExpression(node, lvl);
  if (node->is_typed(cdk::TYPE_DOUBLE))
    _pf.DMUL();
  else
    _pf.MUL();
}

void til::postfix_writer::do_div_node(cdk::div_node * const node, int lvl) {
  do_PIDBinaryExpression(node, lvl);
  if (node->is_typed(cdk::TYPE_DOUBLE))
    _pf.DDIV();
  else
    _pf.DIV();
}

void til::postfix_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MOD();
}

//---------------------------------------------------------------------------

void til::postfix_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  do_GeneralLogicalBinaryExpression(node, lvl);
  _pf.LT();
}

void til::postfix_writer::do_le_node(cdk::le_node * const node, int lvl) {
  do_GeneralLogicalBinaryExpression(node, lvl);
  _pf.LE();
}

void til::postfix_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  do_GeneralLogicalBinaryExpression(node, lvl);
  _pf.GE();
}

void til::postfix_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  do_GeneralLogicalBinaryExpression(node, lvl);
  _pf.GT();
}

void til::postfix_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  do_GeneralLogicalBinaryExpression(node, lvl);
  _pf.NE();
}

void til::postfix_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  do_GeneralLogicalBinaryExpression(node, lvl);
  _pf.EQ();
}

//---------------------------------------------------------------------------

void til::postfix_writer::do_variable_node(cdk::variable_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  const auto symbol = _symtab.find(node->name());
  // check if it is EXTERNAL before checking if it is GLOBAL,
  // as otherwise we wouldn't be CALLing it, but rather BRANCHing to it
  if (symbol->qualifier() == tEXTERNAL)
    // if it's been forwarded, we won't branch to it, but rather call it;
    // as such, we require its label (useful in
    // function calls)
    _currentForwardLabel = symbol->name();
  else if (symbol->is_global())
  // global variable
    _pf.ADDR(symbol->name());
  else
  // inside a function
    _pf.LOCAL(symbol->offset());
}

void til::postfix_writer::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->lvalue()->accept(this, lvl);
  if(node->is_typed(cdk::TYPE_DOUBLE))
    _pf.LDDOUBLE();
  else{
    if(_currentForwardLabel.empty()) 
      _pf.LDINT();
// else{
//   we are CALLing a function by its LABEL,
//   so we don't need to LOAD anything
// }
  }
}

void til::postfix_writer::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->rvalue()->accept(this, lvl + 2);
  if(node->is_typed(cdk::TYPE_DOUBLE)){
    if(node->rvalue()->is_typed(cdk::TYPE_INT))
      _pf.I2D();
    _pf.DUP64();
  }
  else{
    _pf.DUP32();
  }

  node->lvalue()->accept(this, lvl);
  if(node->is_typed(cdk::TYPE_DOUBLE))
    _pf.STDOUBLE();
  else
    _pf.STINT();
}

//---------------------------------------------------------------------------

void til::postfix_writer::do_evaluation_node(til::evaluation_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
  _pf.TRASH(node->argument()->type()->size()); // delete it
}

void til::postfix_writer::do_print_node(til::print_node * const node, int lvl) {
  //TODO: check if this is correct
  ASSERT_SAFE_EXPRESSIONS;
  std::map<int, std::pair<std::string, int>> printFunctions = {
    {cdk::TYPE_INT, {"printi", 4}},
    {cdk::TYPE_DOUBLE, {"printd", 8}},
    {cdk::TYPE_STRING, {"prints", 4}}
  };

  for (size_t ix = 0; ix < node->arguments()->size(); ix++) {
    const auto arg = dynamic_cast<cdk::expression_node *>(node->arguments()->node(ix));
    arg->accept(this, lvl); // determine the value to print

    auto it = printFunctions.find(arg->type()->name());
    if (it != printFunctions.end()) {
      _functionsToDeclare.insert(it->second.first);
      _pf.CALL(it->second.first);
      _pf.TRASH(it->second.second); // delete the printed value from the stack
    } else {
      error(node->lineno(), "Unknown type for printable expression");
    }
  }

  if (node->newline()) {
    _functionsToDeclare.insert("println");
    _pf.CALL("println");
  }
}

//---------------------------------------------------------------------------

void til::postfix_writer::do_read_node(til::read_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  switch (node->type()->name()) {
  case cdk::TYPE_INT:
  case cdk::TYPE_UNSPEC: // cases like `auto x = input;`
    _functionsToDeclare.insert("readi");
    _pf.CALL("readi");
    _pf.LDFVAL32();
    break;
  case cdk::TYPE_DOUBLE:
    _functionsToDeclare.insert("readd");
    _pf.CALL("readd");
    _pf.LDFVAL64();
    break;
  default:
    error(node->lineno(), "cannot read expression of unknown type");
  }
}

//---------------------------------------------------------------------------

void til::postfix_writer::do_loop_node(til::loop_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int loopCondLbl = ++_lbl;
  int loopEndLbl = ++_lbl;
  _loopCond.push_back(
      loopCondLbl); // the (currently) deepest loop condition label
  _loopEnd.push_back(loopEndLbl); // the (currently) deepest loop end label

  _symtab.push(); // entering new context, new symbol table for block-local vars

  _pf.ALIGN();                              // make sure we are aligned
  _pf.LABEL(mklbl(loopCondLbl));           // setting label for the condition
  node->condition()->accept(this, lvl + 2); // condition evaluation
  _pf.JZ(mklbl(loopEndLbl));               // if false, exit the cycle

  node->block()->accept(this, lvl + 2); // block evaluation
  _lastBlockInstrSeen = false;
  _pf.JMP(mklbl(loopCondLbl));  // repeat
  _pf.ALIGN();                   // make sure we are aligned
  _pf.LABEL(mklbl(loopEndLbl)); // setting label for the end of the cycle

  _symtab.pop();         // leaving current context
  _loopCond.pop_back(); // leaving current loop condition label
  _loopEnd.pop_back();  // leaving current loop end label
}

//---------------------------------------------------------------------------

void til::postfix_writer::do_if_node(til::if_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl = ++_lbl;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl));
  node->block()->accept(this, lvl + 2);
  _lastBlockInstrSeen = false;
  _pf.LABEL(mklbl(lbl));
}

//---------------------------------------------------------------------------

void til::postfix_writer::do_if_else_node(til::if_else_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1, lbl2;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->thenblock()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl2 = ++_lbl));
  _pf.LABEL(mklbl(lbl1));
  node->elseblock()->accept(this, lvl + 2);
  _lastBlockInstrSeen = false;
  _pf.LABEL(mklbl(lbl1 = lbl2));
}

//---------------------------------------------------------------------------

void til::postfix_writer::do_block_node(til::block_node * const node, int lvl) {
  _symtab.push();
  if (node->declarations())
    node->declarations()->accept(this, lvl + 2);
  if (node->instructions())
    node->instructions()->accept(this, lvl + 2);
  _symtab.pop();
}

//---------------------------------------------------------------------------

void til::postfix_writer::do_stop_node(til::stop_node * const node, int lvl) {
  const auto loopLabels = _loopCond.size();
  if (loopLabels == 0) {
    error(node->lineno(), "stop node found outside a loop block");
    return;
  }
  const size_t stopLvl = (size_t)node->level();
  if (stopLvl > loopLabels || stopLvl < 1) {
    error(node->lineno(), "invalid stop level");
    return;
  }
  _lastBlockInstrSeen = true;
  const auto loopEndLbl = _loopEnd[loopLabels - stopLvl];
  _pf.JMP(mklbl(loopEndLbl));
}

//---------------------------------------------------------------------------

void til::postfix_writer::do_next_node(til::next_node * const node, int lvl) {
  const auto loopLabels = _loopCond.size();
  if (loopLabels == 0) {
    error(node->lineno(), "next node found outside a loop block");
    return;
  }
  const size_t nextLvl = (size_t)node->level();
  if (nextLvl > loopLabels || nextLvl < 1) {
    error(node->lineno(), "invalid next level");
    return;
  }
  _lastBlockInstrSeen = true;
  const auto loopCondLbl = _loopCond[loopLabels - nextLvl];
  _pf.JMP(mklbl(loopCondLbl));
}

//---------------------------------------------------------------------------

void til::postfix_writer::do_return_node(til::return_node * const node, int lvl) {
  // TODO: check if this is correct
  ASSERT_SAFE_EXPRESSIONS;
  // should not reach here without returning a value (if not void)
  const auto current_function_type_name =
      cdk::functional_type::cast(_functions.back()->type())->output(0)->name();

  if (current_function_type_name != cdk::TYPE_VOID) {
    node->value()->accept(this, lvl + 2);
    switch (current_function_type_name) {
    case cdk::TYPE_INT:
      // allowing covariant return types (i.e., double is considered a valid
      // return type to cast from int) we'll always return doubles from non-main
      // functions instead of ints, to allow covariance the second part of this
      // logic is handled in the function call's visitor, where we _load_ the
      // return value, which should be the address of the first instruction of
      // the function being called
      // !!! the exception is main, since it returns 0 (int) per convention
      if (_functions.back()->is_main()) {
        _mainReturnSeen = true;
        _pf.STFVAL32();
      } else {
        _pf.I2D();
        _pf.STFVAL64();
      }
      break;
    case cdk::TYPE_STRING:
    case cdk::TYPE_POINTER:
    case cdk::TYPE_FUNCTIONAL:
      _pf.STFVAL32(); // removes 4 bytes from the stack
      break;
    case cdk::TYPE_DOUBLE:
      if (!node->value()->is_typed(cdk::TYPE_DOUBLE))
        _pf.I2D();    // converts int to double
      _pf.STFVAL64(); // removes 8 bytes (a double) from the stack
      break;
    default:
      error(node->lineno(), "invalid return type");
    }
  }

  _lastBlockInstrSeen = true;
  _pf.LEAVE();
  _pf.RET();}

//---------------------------------------------------------------------------

void til::postfix_writer::do_index_node(til::index_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->base()->accept(this, lvl);
  node->index()->accept(this, lvl);
  _pf.INT(node->type()->size()); // type size
  _pf.MUL(); // type size * index
  _pf.ADD(); // base + (type size * index)
}

//---------------------------------------------------------------------------

void til::postfix_writer::do_address_of_node(til::address_of_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl + 2);}

//---------------------------------------------------------------------------

void til::postfix_writer::do_sizeof_node(til::sizeof_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  if (_inFuncBody)
    _pf.INT(node->argument()->type()->size());
  else
    _pf.SINT(node->argument()->type()->size());
}

//---------------------------------------------------------------------------

void til::postfix_writer::do_function_definition_node(til::function_definition_node * const node, int lvl) {
  // TODO: check if this is correct
  node->main() ? do_MainFunction(node, lvl)
               : do_NonMainFunction(node, lvl);
}

//---------------------------------------------------------------------------

void til::postfix_writer::do_function_call_node(til::function_call_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  std::vector<std::shared_ptr<cdk::basic_type>> arg_types;
  const auto function = node->function();
  if (function)
    // in non recursive calls, the arguments are already stored in the node
    // itself
    arg_types =
        cdk::functional_type::cast(function->type())->input()->components();
  else {
    // in recursive calls, we'll want to fetch the symbol associated with
    // the deepest function we can find, and retrieve its arguments
    auto deepest_function = _functions.back();
    arg_types = cdk::functional_type::cast(deepest_function->type())
                    ->input()
                    ->components();
  }

  size_t args_size = 0; // size of all the arguments in bytes
  if (node->arguments()) {
    for (int i = node->arguments()->size() - 1; i >= 0; i--) {
      auto arg =
          dynamic_cast<cdk::expression_node *>(node->arguments()->node(i));
      arg->accept(this, lvl + 2);
      if (arg_types[i]->name() == cdk::TYPE_DOUBLE &&
          arg->type()->name() == cdk::TYPE_INT) {
        args_size += 4; // if we're passing an integer where a double is
                        // expected, we need to allocate 4 additional bytes
        _pf.I2D();      // also need to convert integer to double
      }
      args_size += arg->type()->size();
    }
  }

  // there are 3 cases now: we may want to do a recursive, non-recursive
  // "regular", or forwarded call
  if (function) {
    // non-recursive calls
    _currentForwardLabel.clear();
    // if we accept a forwarded function, the label will once again be set
    function->accept(this, lvl + 2);
    if (_currentForwardLabel.empty()) // it's a "regular" non-recursive call
      _pf.BRANCH();
    else // it's a forwarded call
      _pf.CALL(_currentForwardLabel);
  } else {
    // recursive calls
    _pf.CALL(_functionLabels.back());
  }

  if (args_size > 0)
    _pf.TRASH(args_size); // removes no-longer-needed arguments from the stack

  switch (node->type()->name()) {
  case cdk::TYPE_VOID:
    break;
  case cdk::TYPE_INT:
    if (_currentForwardLabel.empty()) {
      // the second part of allowing covariance to happen (with the first one
      // being handled in the return node's visitor) there, we make every
      // non-main int-returning function actually return a double here, we
      // convert that double back to an int, as it is the callee's
      // responsibility to properly cast the return values
      _pf.LDFVAL64();
      _pf.D2I();
    } else {
      // note how in forwarded methods we don't need to do any conversion, as
      // the return value is already an int
      _pf.LDFVAL32();
    }
    break;
  case cdk::TYPE_STRING:
  case cdk::TYPE_POINTER:
  case cdk::TYPE_FUNCTIONAL:
    _pf.LDFVAL32();
    break;
  case cdk::TYPE_DOUBLE:
    _pf.LDFVAL64();
    break;
  default: // can't happen!
    error(node->lineno(), "cannot call expression of unknown type");
  }

  _currentForwardLabel
      .clear(); // we're done with this label, so we can clear it
}

//---------------------------------------------------------------------------

void til::postfix_writer::do_declaration_node(til::declaration_node * const node, int lvl) {
  // TODO: check if this is correct
  ASSERT_SAFE_EXPRESSIONS;
  const auto id = node->identifier();
  const auto type_size = node->type()->size(); // size in bytes
  int offset = 0;                              // will be kept 0 if global

  if (_inFuncArgs) {
    // the function's arguments are placed in the stack by the caller
    offset = _offset;
    _offset += type_size;
  } else if (_inFuncBody) {
    // the function's local variables are placed in the stack by the callee
    _offset -= type_size;
    offset = _offset;
  }

  const auto symbol = new_symbol();
  if (symbol) {
    symbol->set_offset(offset);
    reset_new_symbol();
  }

  // we may still need to initialize the variable
  if (node->init()) {
    if (_inFuncBody)
      do_LocalVarInit(symbol, node->init(), lvl);
    else
      do_GlobalVarInit(symbol, node->init(), lvl);
    _symbolsToDeclare.erase(symbol->name());
  } else if (!_inFuncArgs && !_inFuncBody)
    _symbolsToDeclare.insert(symbol->name());}

//---------------------------------------------------------------------------

void til::postfix_writer::do_stack_alloc_node(til::stack_alloc_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl);
  _pf.INT(cdk::reference_type::cast(node->type())
          ->referenced()->size()); // type size
  _pf.MUL(); // type size * argument
  _pf.ALLOC(); // allocate space for the array
  _pf.SP(); // pushes the array's address
}

//---------------------------------------------------------------------------

void til::postfix_writer::do_nullptr_node(til::nullptr_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  // a pointer is a 32-bit integer value
  if (_inFuncBody)
    _pf.INT(0); // nullptr is zero
  else
    _pf.SINT(0); // nullptr is zero
}

//--------------------------------------------------------------------------------

void til::postfix_writer::do_with_node(til::with_node * const node, int lvl){
  ASSERT_SAFE_EXPRESSIONS;
  auto startlbl = mklbl(++_lbl);
  auto endlbl = mklbl(++_lbl);

  auto func = cdk::functional_type::cast(node->function()->type());
  auto ref = cdk::reference_type::cast(node->vector()->type())->referenced();

  node->low()->accept(this, lvl + 2);

  _pf.ALIGN();
  _pf.LABEL(startlbl);
  _pf.DUP32();
  node->high()->accept(this, lvl + 2);
  _pf.LT();
  _pf.JZ(endlbl); // false
  _pf.DUP32();
  //low*type+addr
  _pf.INT(ref->size());
  _pf.MUL();
  node->vector()->accept(this, lvl+2);
  _pf.ADD();
  //alr got right addr (low addr)
  if(ref->name() == cdk::TYPE_INT && func->input(0)->name() == cdk::TYPE_DOUBLE){
    //convert to double
    _pf.LDINT();
    _pf.I2D();
  }

  else if(func->input(0)->name() == cdk::TYPE_DOUBLE){ /* both double */
    _pf.LDDOUBLE();
  }
  else /* both ints */{
    _pf.LDINT();
  }
  //alr got arg


  //call fun
  _currentForwardLabel.clear();
  // if we accept a forwarded function, the label will once again be set
  node->function()->accept(this, lvl + 2);
  if (_currentForwardLabel.empty()) // it's a "regular" non-recursive call
    _pf.BRANCH();
  else // it's a forwarded call
    _pf.CALL(_currentForwardLabel);

  // trash input value
  _pf.TRASH(func->input(0)->name() == cdk::TYPE_DOUBLE ? 8 : 4);

  //next iteration
  _pf.INT(1);
  _pf.ADD();
  _pf.JMP(startlbl);

  //end
  _pf.ALIGN();
  _pf.LABEL(endlbl);
  _pf.TRASH(4);

}

//--------------------------------------------------------------------------------

void til::postfix_writer::do_unless_node(til::unless_node * const node, int lvl){
  ASSERT_SAFE_EXPRESSIONS;


  // for loop through vector start at zero go to value apply function in all of them
  auto startlabel = mklbl(++_lbl);
  auto endlabel = mklbl(++_lbl);

  auto func = cdk::functional_type::cast(node->function()->type());
  auto ref = cdk::reference_type::cast(node->pointer()->type())->referenced();
  // if condition jump end
  node->condition()->accept(this, lvl+2);
  _pf.JNZ(endlabel);

  // else
  _pf.INT(0);
  _pf.ALIGN();
  _pf.LABEL(startlabel);
  _pf.DUP32();

  node->value()->accept(this, lvl+2);
  _pf.LE();
  _pf.JZ(endlabel);

  _pf.DUP32();
  _pf.INT(ref->size());
  _pf.MUL();
  node->pointer()->accept(this, lvl+2);
  _pf.ADD();
  // check types
  if(ref->name() == cdk::TYPE_INT && func->input(0)->name() == cdk::TYPE_DOUBLE){
    _pf.LDINT();
    _pf.I2D();
  }

  else if(func->input(0)->name() == cdk::TYPE_DOUBLE){
    _pf.LDDOUBLE();
  }

  else{
    _pf.LDINT();
  }

  //count and arg in stack
  _currentForwardLabel.clear();
  // if we accept a forwarded function, the label will once again be set
  node->function()->accept(this, lvl + 2);
  if (_currentForwardLabel.empty()) // it's a "regular" non-recursive call
    _pf.BRANCH();
  else // it's a forwarded call
    _pf.CALL(_currentForwardLabel);

  _pf.TRASH(func->input(0)->name() == cdk::TYPE_DOUBLE ? 8 : 4);

  //delete output
  if(func->output(0)->name() == cdk::TYPE_DOUBLE){
    _pf.LDFVAL64();
    _pf.TRASH(8);
  }

  else if(!(func->output(0)->name() == cdk::TYPE_VOID)){
    _pf.LDFVAL32();
    _pf.TRASH(4);
  }

  _pf.INT(1);
  _pf.ADD();
  _pf.JMP(startlabel);

  _pf.ALIGN();
  _pf.LABEL(endlabel);
  _pf.TRASH(4);

}

//--------------------------------------------------------------------------------

void til::postfix_writer::do_sweep_node(til::sweep_node * const node, int lvl){
  ASSERT_SAFE_EXPRESSIONS;
  //iterate through vector and call func if cond verifies

  auto startlbl = mklbl(++_lbl);
  auto incrementlbl = mklbl(++_lbl);
  auto endlbl = mklbl(++_lbl);

  auto func = cdk::functional_type::cast(node->function()->type());
  auto ref = cdk::reference_type::cast(node->vector()->type())->referenced();

  node->low()->accept(this, lvl+2);

  _pf.ALIGN();
  _pf.LABEL(startlbl);
  _pf.DUP32();
  node->high()->accept(this, lvl+2);
  _pf.LT();
  _pf.JZ(endlbl);

  _pf.DUP32();
  _pf.INT(ref->size());
  _pf.MUL();

  node->vector()->accept(this, lvl+2);
  _pf.ADD();

  if(func->input(0)->name() == cdk::TYPE_DOUBLE && ref->name() == cdk::TYPE_INT){
    _pf.LDINT();
    _pf.I2D();
  }

  else if(func->input(0)->name() == cdk::TYPE_DOUBLE){
    _pf.LDDOUBLE();
  }

  else{
    _pf.LDINT();
  }

  //arg value on stack

  //check condition
  node->condition()->accept(this, lvl+2);
  _pf.JZ(incrementlbl);

  _currentForwardLabel.clear();
  // if we accept a forwarded function, the label will once again be set
  node->function()->accept(this, lvl + 2);
  if (_currentForwardLabel.empty()) // it's a "regular" non-recursive call
    _pf.BRANCH();
  else // it's a forwarded call
    _pf.CALL(_currentForwardLabel);

  _pf.TRASH(func->input(0)->name() == cdk::TYPE_DOUBLE ? 8 : 4);

  // delete output that is in registers


  _pf.ALIGN();
  _pf.LABEL(incrementlbl);
  _pf.INT(1);
  _pf.ADD();
  _pf.JMP(startlbl);


  _pf.ALIGN();
  _pf.LABEL(endlbl);
  _pf.TRASH(4);
}


void til::postfix_writer::do_change_node(til::change_node * const node, int lvl){
  ASSERT_SAFE_EXPRESSIONS;
  auto startlbl = mklbl(++_lbl);
  auto endlbl = mklbl(++_lbl);

  auto func = cdk::functional_type::cast(node->function()->type());
  auto vec = cdk::reference_type::cast(node->vector()->type())->referenced();

  node->low()->accept(this, lvl+2);
  //low na stack

  _pf.ALIGN();
  _pf.LABEL(startlbl);
  _pf.DUP32();
  node->high()->accept(this, lvl+2);
  _pf.LT();
  _pf.JZ(endlbl);

  //get argument

  _pf.DUP32();
  _pf.INT(vec->size());
  _pf.MUL();
  node->vector()->accept(this, lvl+2);
  _pf.ADD();

  //addr on stack
  _pf.DUP32(); // will need the addr for later
  _pf.DUP32();
  if(func->input(0)->name() == cdk::TYPE_DOUBLE && vec->name() == cdk::TYPE_INT){
    _pf.LDINT();
    _pf.I2D();
  }
  else if(func->input(0)->name() == cdk::TYPE_DOUBLE){
    _pf.LDDOUBLE();
  }
  else{
    _pf.LDINT();
  }

  //value in stack
  _currentForwardLabel.clear();
  // if we accept a forwarded function, the label will once again be set
  node->function()->accept(this, lvl + 2);
  if (_currentForwardLabel.empty()) // it's a "regular" non-recursive call
    _pf.BRANCH();
  else // it's a forwarded call
    _pf.CALL(_currentForwardLabel);

  _pf.TRASH(func->input(0)->name() == cdk::TYPE_DOUBLE ? 8 : 4);
  
  //get return value and store it in the vector

  if(func->output(0)->name() == cdk::TYPE_DOUBLE){
    _pf.LDFVAL64();
    _pf.SWAP64();
    _pf.TRASH(4);
    _pf.STDOUBLE();

  }
  else if(!(func->output(0)->name() == cdk::TYPE_VOID)){
    _pf.LDFVAL32();
    _pf.SWAP32();
    _pf.STINT();
    _pf.TRASH(4);
  }
  else{
    _pf.TRASH(8);
  }

  //increment
  _pf.INT(1);
  _pf.ADD();
  _pf.JMP(startlbl);

  _pf.ALIGN();
  _pf.LABEL(endlbl);
  _pf.TRASH(4);

}