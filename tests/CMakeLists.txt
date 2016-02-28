#!/bin/bash
#
# The MIT License (MIT)
#
# Copyright (c) 2016 Yanzheng Li
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


# Build executable `run_tests`.
add_executable(run_tests
    memory/allocation_policy_unittest.cc
    memory/allocator_unittest.cc
    memory/block_allocator_unittest.cc
    memory/object_container_unittest.cc
    dyobj/dynamic_object_heap_unittest.cc
    dyobj/dynamic_object_unittest.cc
    dyobj/heap_allocator_unittest.cc
    gc/garbage_collection_unittest.cc
    types/binary_operators_unittest.cc
    types/interfaces_test.cc
    types/native_array_type_interfaces_test.cc
    types/native_array_unittest.cc
    types/native_map_type_interfaces_test.cc
    types/native_map_unittest.cc
    types/native_string_type_interfaces_test.cc
    types/native_string_unittest.cc
    types/native_type_handle_unittest.cc
    types/unary_operators_unittest.cc
    types/variant_unittest.cc
    runtime/compartment_unittest.cc
    runtime/frame_unittest.cc
    runtime/instr_info_unittest.cc
    runtime/instrs_unittest.cc
    runtime/invocation_ctx_unittest.cc
    runtime/native_types_pool_unittest.cc
    runtime/process_unittest.cc
    runtime/sighandler_registrar_unittest.cc
    runtime/utils_unittest.cc
    frontend/configuration_unittest.cc
    frontend/program_unittest.cc
    frontend/runner_unittest.cc
    frontend/signal_vector_loader_unittest.cc
    frontend/utils_unittest.cc
    main.cc
    )


set_target_properties(run_tests PROPERTIES COMPILE_FLAGS "-Wno-weak-vtables -Wno-missing-variable-declarations -O3")


target_link_libraries(run_tests
    corevm
    boost_system
    boost_regex
    boost_iostreams
    boost_program_options
    pthread
    sneaker
    avrocpp_s
    gtest
    )


# Run tests.
add_custom_command(TARGET run_tests POST_BUILD COMMAND
    ./run_tests --gtest_color=yes --gtest_shuffle --gtest_repeat=3)