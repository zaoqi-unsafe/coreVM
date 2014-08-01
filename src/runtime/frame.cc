#include "../../include/runtime/frame.h"


corevm::runtime::frame::frame():
  _return_addr(-1),
  _parent_scope_frame_ptr(nullptr),
  _visible_vars(std::unordered_map<corevm::runtime::variable_key, corevm::dyobj::dyobj_id>()),
  _invisible_vars(std::unordered_map<corevm::runtime::variable_key, corevm::dyobj::dyobj_id>()),
  _params_list(std::stack<corevm::dyobj::dyobj_id>()),
  _param_value_map(std::unordered_map<corevm::runtime::variable_key, corevm::dyobj::dyobj_id>()),
  _eval_stack(std::stack<corevm::types::native_type_handle>())
{
  // Do nothing here.
}

corevm::runtime::frame::~frame()
{
  // Do nothing here.
}

void
corevm::runtime::frame::check_state_before_destruction() throw(corevm::runtime::evaluation_stack_not_empty_error)
{
  // Validation checks on the state of the frame before it gets destroyed.
  if(!_eval_stack.empty()) {
    throw corevm::runtime::evaluation_stack_not_empty_error();
  }
}

corevm::runtime::instr_addr
corevm::runtime::frame::get_return_addr() const
{
  return _return_addr;
}

void
corevm::runtime::frame::set_return_addr(const corevm::runtime::instr_addr return_addr)
{
  _return_addr = return_addr;
}

corevm::runtime::frame*
corevm::runtime::frame::get_parent_scope_frame_ptr() const
{
  return _parent_scope_frame_ptr;
}

void
corevm::runtime::frame::set_parent_scope_frame_ptr(corevm::runtime::frame* ptr)
{
  _parent_scope_frame_ptr = ptr;
}

void
corevm::runtime::frame::push_eval_stack(corevm::types::native_type_handle& operand)
{
  _eval_stack.push(operand);
}

corevm::types::native_type_handle
corevm::runtime::frame::pop_eval_stack() throw(corevm::runtime::evaluation_stack_empty_error)
{
  if(_eval_stack.empty()) {
    throw corevm::runtime::evaluation_stack_empty_error();
  }

  corevm::types::native_type_handle operand = _eval_stack.top();
  _eval_stack.pop(); 
  return operand;
}

bool
corevm::runtime::frame::has_visible_var(const corevm::runtime::variable_key var_key)
{
  return _visible_vars.find(var_key) != _visible_vars.end();
}

corevm::dyobj::dyobj_id
corevm::runtime::frame::get_visible_var(
  const corevm::runtime::variable_key var_key) throw(corevm::runtime::local_variable_not_found_error)
{
  if(!has_visible_var(var_key)) {
    throw corevm::runtime::local_variable_not_found_error();
  }

  return _visible_vars.at(var_key);
};

corevm::dyobj::dyobj_id
corevm::runtime::frame::pop_visible_var(
  const corevm::runtime::variable_key var_key) throw(corevm::runtime::local_variable_not_found_error)
{
  corevm::dyobj::dyobj_id obj_id = get_visible_var(var_key);
  _visible_vars.erase(var_key);
  return obj_id;
}

void
corevm::runtime::frame::set_visible_var(
  corevm::runtime::variable_key var_key, corevm::dyobj::dyobj_id obj_id)
{
  _visible_vars[var_key] = obj_id;
}

bool
corevm::runtime::frame::has_invisible_var(const corevm::runtime::variable_key var_key)
{
  return _invisible_vars.find(var_key) != _visible_vars.end();
}

corevm::dyobj::dyobj_id
corevm::runtime::frame::get_invisible_var(
  const corevm::runtime::variable_key var_key) throw(corevm::runtime::local_variable_not_found_error)
{
  if(!has_invisible_var(var_key)) {
    throw corevm::runtime::local_variable_not_found_error();
  }

  return _invisible_vars.at(var_key);
};

corevm::dyobj::dyobj_id
corevm::runtime::frame::pop_invisible_var(
  const corevm::runtime::variable_key var_key) throw(corevm::runtime::local_variable_not_found_error)
{
  corevm::dyobj::dyobj_id obj_id = get_invisible_var(var_key);
  _invisible_vars.erase(var_key);
  return obj_id;
}

void
corevm::runtime::frame::set_invisible_var(
  corevm::runtime::variable_key var_key, corevm::dyobj::dyobj_id obj_id)
{
  _invisible_vars[var_key] = obj_id;
}