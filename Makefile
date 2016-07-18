# The MIT License (MIT)

# Copyright (c) 2016 Yanzheng Li

# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


## Top level Makefile. Used to bootstrap cmake to build from source.


## -----------------------------------------------------------------------------

TOP_DIR=$(CURDIR)
BUILD_DIR=$(TOP_DIR)/build
BUILD_GCC_DIR=$(TOP_DIR)/build_gcc
PYTHON_DIR=python
PYTHON_TESTS_DIR=$(PYTHON_DIR)/tests
BOOTSTRAP_TESTS=bootstrap_tests.py
BOOTSTRAP_TESTS_ARGS=
DOCS_DIR=./docs
DOCS_BUILD_DIR=$(DOCS_DIR)/build
SANITY_TESTS_ARGS=--sanity-test
DYNAMIC_ANALYSIS_TESTS_ARGS=--dynamic-analysis
PYTHON=`which python`

## -----------------------------------------------------------------------------

BASE_TARGETS=build python_tests docs

ifeq ($(full), 1)
	BUILD_TARGETS=$(BASE_TARGETS) benchmarks
	BUILD_TARGET_CMAKE_ARGS=-DBUILD_BENCHMARKS=ON
else ifeq ($(full), 2)
	BUILD_TARGETS=$(BASE_TARGETS) benchmarks sanity_tests dynamic_analysis_tests
	BUILD_TARGET_CMAKE_ARGS=-DBUILD_BENCHMARKS=ON -DBUILD_SANITY_BIN=ON
else
	BUILD_TARGETS=$(BASE_TARGETS)
	BUILD_TARGET_CMAKE_ARGS=
endif

ifeq ($(travis_ci), 1)
	BUILD_TARGET_CMAKE_ARGS+=-DBUILD_BENCHMARKS_STRICT=OFF
endif

ifeq ($(build_gcc_target), 1)
	BUILD_TARGETS+=build_gcc
endif

BUILD_GCC_TARGET_CMAKE_ARGS=-DCMAKE_CXX_COMPILER=g++

## -----------------------------------------------------------------------------

.PHONY: all
all: $(BUILD_TARGETS)

## -----------------------------------------------------------------------------

.PHONY: build
build:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR); cmake $(BUILD_TARGET_CMAKE_ARGS) ../ && make

## -----------------------------------------------------------------------------

.PHONY:
build_gcc:
	@echo "Compiling using GCC..."
	mkdir -p $(BUILD_GCC_DIR)
	cd $(BUILD_GCC_DIR); cmake $(BUILD_TARGET_CMAKE_ARGS) $(BUILD_GCC_TARGET_CMAKE_ARGS) ../ && make

## -----------------------------------------------------------------------------

.PHONY: python_tests
python_tests:
	$(PYTHON) $(PYTHON_DIR)/$(BOOTSTRAP_TESTS) $(BOOTSTRAP_TESTS_ARGS)

## -----------------------------------------------------------------------------

.PHONY: docs
docs:
	$(MAKE) -C docs html

## -----------------------------------------------------------------------------

.PHONY: sanity_tests
sanity_tests:
	export ASAN_SYMBOLIZER_PATH=$(which llvm-symbolizer-3.4)
	$(PYTHON) $(PYTHON_DIR)/$(BOOTSTRAP_TESTS) $(SANITY_TESTS_ARGS)

## -----------------------------------------------------------------------------

.PHONY: dynamic_analysis_tests
dynamic_analysis_tests:
	$(PYTHON) $(PYTHON_DIR)/$(BOOTSTRAP_TESTS) $(DYNAMIC_ANALYSIS_TESTS_ARGS)

## -----------------------------------------------------------------------------

.PHONY: benchmarks
benchmarks:
	$(BUILD_DIR)/benchmarks/run_benchmarks

## -----------------------------------------------------------------------------

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(BUILD_GCC_DIR)
	rm -f $(PYTHON_TESTS_DIR)/*.tmp.py
	rm -f $(PYTHON_TESTS_DIR)/*.tmp.py.core
	rm -rf $(DOCS_BUILD_DIR)/*

## -----------------------------------------------------------------------------
