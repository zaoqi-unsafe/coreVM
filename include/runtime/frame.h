#ifndef COREVM_FRAME_H_
#define COREVM_FRAME_H_

#include <list>
#include <stack>
#include "common.h"
#include "errors.h"
#include "../../include/dyobj/dyobj_id.h"
#include "../../include/types/native_type_handle.h"


namespace corevm {


namespace runtime {


/* Each frame is supposed to have:
 *
 * - Return address.
 * - Pointer to the address caller frame.
 * - Pointer to frame with parent scope (if has one).
 * - Visible local variables.
 * - Invisible local variables.
 * - Parameter list (args).
 * - Optional parameter <-> default value mapping (kwargs).
 * - Evaluation stack.
 * */
class frame {
public:
  explicit frame();
  ~frame();

  void check_state_before_destruction() throw(corevm::runtime::evaluation_stack_not_empty_error);

  uint32_t eval_stack_size() const;

  corevm::runtime::instr_addr get_start_addr() const;
  void set_start_addr(const corevm::runtime::instr_addr);

  corevm::runtime::instr_addr get_return_addr() const;
  void set_return_addr(const corevm::runtime::instr_addr);

  corevm::runtime::frame* get_parent_scope_frame_ptr() const;
  void set_parent_scope_frame_ptr(corevm::runtime::frame*);

  void push_eval_stack(corevm::types::native_type_handle&);
  corevm::types::native_type_handle pop_eval_stack() throw(corevm::runtime::evaluation_stack_empty_error);

  bool has_visible_var(const corevm::runtime::variable_key);
  corevm::dyobj::dyobj_id get_visible_var(const corevm::runtime::variable_key) throw(corevm::runtime::local_variable_not_found_error);
  corevm::dyobj::dyobj_id pop_visible_var(const corevm::runtime::variable_key) throw(corevm::runtime::local_variable_not_found_error);
  void set_visible_var(corevm::runtime::variable_key, corevm::dyobj::dyobj_id);

  bool has_invisible_var(const corevm::runtime::variable_key);
  corevm::dyobj::dyobj_id get_invisible_var(const corevm::runtime::variable_key) throw(corevm::runtime::local_variable_not_found_error);
  corevm::dyobj::dyobj_id pop_invisible_var(const corevm::runtime::variable_key) throw(corevm::runtime::local_variable_not_found_error);
  void set_invisible_var(corevm::runtime::variable_key, corevm::dyobj::dyobj_id);

  bool has_params() const;
  void put_param(const corevm::dyobj::dyobj_id&);
  const corevm::dyobj::dyobj_id pop_param() throw(corevm::runtime::missing_parameter_error);

  bool has_param_value_pairs() const;
  void put_param_value_pair(const corevm::runtime::variable_key, const corevm::dyobj::dyobj_id&);
  const corevm::dyobj::dyobj_id pop_param_value_pair(const corevm::runtime::variable_key) throw(corevm::runtime::missing_parameter_error);
  std::list<corevm::runtime::variable_key> param_value_pair_keys() const;

  std::list<corevm::dyobj::dyobj_id> get_visible_objs() const;
  std::list<corevm::dyobj::dyobj_id> get_invisible_objs() const;

protected:
  corevm::runtime::instr_addr _start_addr = corevm::runtime::NONESET_INSTR_ADDR;
  corevm::runtime::instr_addr _return_addr = corevm::runtime::NONESET_INSTR_ADDR;
  corevm::runtime::frame* _parent_scope_frame_ptr = nullptr;
  std::unordered_map<corevm::runtime::variable_key, corevm::dyobj::dyobj_id> _visible_vars;
  std::unordered_map<corevm::runtime::variable_key, corevm::dyobj::dyobj_id> _invisible_vars;
  std::list<corevm::dyobj::dyobj_id> _params_list;
  std::unordered_map<corevm::runtime::variable_key, corevm::dyobj::dyobj_id> _param_value_map;
  std::stack<corevm::types::native_type_handle> _eval_stack;
};


}; /* end namespace runtime */


}; /* end namespace corevm */


#endif /* COREVM_FRAME_H_ */
