/*******************************************************************************
The MIT License (MIT)

Copyright (c) 2017 Yanzheng Li

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
#ifndef COREVM_RUNTIME_VALUE_H_
#define COREVM_RUNTIME_VALUE_H_

#include <llvm/ADT/APInt.h>
#include <vector>

namespace corevm {
namespace jit {

/**
 * Represents a generic runtime value.
 */
struct RuntimeValue {
  union {
    double DoubleVal;
    float FloatVal;
    void* PointerVal;
  };
  llvm::APInt IntVal;

  // TODO: consider using `llvm::SmallVector<>` here.
  std::vector<RuntimeValue> AggregateVal;
};

} /* end namespace jit */
} /* end namespace corevm */

#endif /* COREVM_RUNTIME_VALUE_H_ */
