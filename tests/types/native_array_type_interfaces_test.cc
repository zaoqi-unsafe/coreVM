#include <string>
#include "native_type_interfaces_test_base.h"


class native_array_type_interfaces_test : public native_type_interfaces_test_base {};


TEST_F(native_array_type_interfaces_test, TestGetSize)
{
  corevm::types::native_array array = {1, 2, 3};
  corevm::types::native_type_handle operand = array;

  size_t expected_result = 3;
  this->apply_interface_and_assert_result<size_t>(operand, corevm::types::interface_array_size, expected_result);
}

TEST_F(native_array_type_interfaces_test, TestEmpty)
{
  corevm::types::native_array array = {1, 2, 3};
  corevm::types::native_type_handle operand = array;

  bool expected_result = false;
  this->apply_interface_and_assert_result<bool>(operand, corevm::types::interface_array_empty, expected_result);
}

TEST_F(native_array_type_interfaces_test, TestAt)
{
  corevm::types::native_array array = {1, 2, 3};
  corevm::types::native_type_handle operand = array;
  corevm::types::native_type_handle index = corevm::types::uint32(1);

  corevm::types::native_array::value_type expected_result = 2;
  this->apply_interface_and_assert_result2<corevm::types::native_array::value_type>(operand, index, corevm::types::interface_array_at, expected_result);
}

TEST_F(native_array_type_interfaces_test, TestFront)
{
  corevm::types::native_array array = {1, 2, 3};
  corevm::types::native_type_handle operand = array;

  corevm::types::native_array::value_type expected_result = 1;
  this->apply_interface_and_assert_result<corevm::types::native_array::value_type>(operand, corevm::types::interface_array_front, expected_result);
}

TEST_F(native_array_type_interfaces_test, TestBack)
{
  corevm::types::native_array array = {1, 2, 3};
  corevm::types::native_type_handle operand = array;

  corevm::types::native_array::value_type expected_result = 3;
  this->apply_interface_and_assert_result<corevm::types::native_array::value_type>(operand, corevm::types::interface_array_back, expected_result);
}

TEST_F(native_array_type_interfaces_test, TestAppend)
{
  corevm::types::native_array array = {1, 2, 3};
  corevm::types::native_type_handle operand = array;
  corevm::types::native_type_handle data = corevm::types::uint64(4);

  corevm::types::native_array expected_result = {1, 2, 3, 4};
  this->apply_interface_and_assert_result2<corevm::types::native_array>(operand, data, corevm::types::interface_array_append, expected_result);
}

TEST_F(native_array_type_interfaces_test, TestPop)
{
  corevm::types::native_array array = {1, 2, 3};
  corevm::types::native_type_handle operand = array;

  corevm::types::native_array expected_result = {1, 2};
  this->apply_interface_and_assert_result<corevm::types::native_array>(operand, corevm::types::interface_array_pop, expected_result);
}

TEST_F(native_array_type_interfaces_test, TestSwap)
{
  corevm::types::native_array array = {1, 2, 3};
  corevm::types::native_type_handle operand = array;
  corevm::types::native_array other_array = {4, 5, 6};
  corevm::types::native_type_handle other_operand = other_array;

  corevm::types::native_array expected_result = {4, 5, 6};
  this->apply_interface_and_assert_result2<corevm::types::native_array>(operand, other_operand, corevm::types::interface_array_swap, expected_result);
}

TEST_F(native_array_type_interfaces_test, TestClear)
{
  corevm::types::native_array array = {1, 2, 3};
  corevm::types::native_type_handle operand = array;

  corevm::types::native_array expected_result;
  this->apply_interface_and_assert_result<corevm::types::native_array>(operand, corevm::types::interface_array_clear, expected_result);
}