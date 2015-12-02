/*******************************************************************************
The MIT License (MIT)

Copyright (c) 2015 Yanzheng Li

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*******************************************************************************/
#include "dyobj/dynamic_object.h"
#include "runtime/compartment.h"
#include "runtime/utils.h"

#include <sneaker/testing/_unittest.h>


// -----------------------------------------------------------------------------

class dummy_dynamic_object_manager {};

// -----------------------------------------------------------------------------

class runtime_utils_unittest : public ::testing::Test
{
public:
  using dynamic_object_type = typename corevm::dyobj::dynamic_object<dummy_dynamic_object_manager>;
};

// -----------------------------------------------------------------------------

static const std::string DUMMY_PATH("");

// -----------------------------------------------------------------------------

TEST_F(runtime_utils_unittest, TestGetAttrKey)
{
  corevm::runtime::compartment compartment(DUMMY_PATH);

  const std::string attr_name("__str__");

  corevm::runtime::encoding_map encoding_map;
  encoding_map.emplace_back(attr_name);

  compartment.set_encoding_map(std::move(encoding_map));

  corevm::runtime::encoding_key attr_key = 0;

  attr_key = corevm::runtime::get_attr_key(
    &compartment, attr_key);

  ASSERT_NE(0, attr_key);
}

// -----------------------------------------------------------------------------

TEST_F(runtime_utils_unittest, TestGetAttrKey2)
{
  corevm::runtime::compartment compartment(DUMMY_PATH);

  const std::string attr_name("__str__");

  corevm::runtime::encoding_map encoding_map;
  encoding_map.emplace_back(attr_name);

  compartment.set_encoding_map(std::move(encoding_map));

  corevm::runtime::encoding_key attr_key = 0;

  std::string actual_attr_name;

  attr_key = corevm::runtime::get_attr_key(
    &compartment, attr_key, &actual_attr_name);

  ASSERT_NE(0, attr_key);
  ASSERT_EQ(attr_name, actual_attr_name);
}

// -----------------------------------------------------------------------------

TEST_F(runtime_utils_unittest, TestGetattr)
{
  const std::string attr_name("__str__");

  corevm::dyobj::attr_key attr_key = corevm::dyobj::hash_attr_str(attr_name);
  corevm::dyobj::dyobj_id attr_id = 123;

  dynamic_object_type obj;
  obj.putattr(attr_key, attr_id);

  ASSERT_EQ(true, obj.hasattr(attr_key));

  auto actual_attr_id = corevm::runtime::getattr(obj, attr_name);

  ASSERT_EQ(attr_id, actual_attr_id);
}

// -----------------------------------------------------------------------------

TEST_F(runtime_utils_unittest, TestGetattr2)
{
  corevm::runtime::compartment compartment(DUMMY_PATH);

  const std::string attr_name("__str__");

  corevm::runtime::encoding_map encoding_map;
  encoding_map.emplace_back(attr_name);

  compartment.set_encoding_map(std::move(encoding_map));

  corevm::runtime::encoding_key attr_encoding_key = 0;

  corevm::dyobj::attr_key attr_key = corevm::dyobj::hash_attr_str(attr_name);
  corevm::dyobj::dyobj_id attr_id = 123;

  dynamic_object_type obj;
  obj.putattr(attr_key, attr_id);

  ASSERT_EQ(true, obj.hasattr(attr_key));

  auto actual_attr_id = corevm::runtime::getattr(
    obj, &compartment, attr_encoding_key);

  ASSERT_EQ(attr_id, actual_attr_id);
}

// -----------------------------------------------------------------------------