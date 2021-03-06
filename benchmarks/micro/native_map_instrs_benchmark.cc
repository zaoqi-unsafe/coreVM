/*******************************************************************************
The MIT License (MIT)

Copyright (c) 2016 Yanzheng Li

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
#include <benchmark/benchmark.h>

#include "runtime/instr.h"
#include "types/native_type_value.h"
#include "types/types.h"

#include "instr_benchmarks_fixture.h"


// -----------------------------------------------------------------------------

using corevm::benchmarks::InstrBenchmarksFixture;

// -----------------------------------------------------------------------------

static
void BenchmarkInstrMAPLEN(benchmark::State& state)
{
  InstrBenchmarksFixture fixture;

  corevm::types::NativeTypeValue oprd = corevm::types::native_map {
    { 1, 11 },
    { 2, 22 },
    { 3, 33 },
  };

  corevm::runtime::Instr instr(0, 0, 0);

  auto frame = &fixture.process().top_frame();
  auto invk_ctx = &fixture.process().top_invocation_ctx();

  while (state.KeepRunning())
  {
    frame->push_eval_stack(oprd);

    corevm::runtime::instr_handler_maplen(
      instr, fixture.process(), &frame, &invk_ctx);
  }
}

// -----------------------------------------------------------------------------

static
void BenchmarkInstrMAPEMP(benchmark::State& state)
{
  InstrBenchmarksFixture fixture;

  corevm::types::NativeTypeValue oprd = corevm::types::native_map {
    { 1, 11 },
    { 2, 22 },
    { 3, 33 },
  };

  corevm::runtime::Instr instr(0, 0, 0);

  auto frame = &fixture.process().top_frame();
  auto invk_ctx = &fixture.process().top_invocation_ctx();

  while (state.KeepRunning())
  {
    frame->push_eval_stack(oprd);

    corevm::runtime::instr_handler_mapemp(
      instr, fixture.process(), &frame, &invk_ctx);
  }
}

// -----------------------------------------------------------------------------

static
void BenchmarkInstrMAPFIND(benchmark::State& state)
{
  InstrBenchmarksFixture fixture;

  corevm::types::NativeTypeValue oprd = corevm::types::native_map {
    { 1, 11 },
    { 2, 22 },
    { 3, 33 },
  };

  corevm::types::NativeTypeValue oprd2 =
    corevm::types::uint32(2);

  corevm::runtime::Instr instr(0, 0, 0);

  auto frame = &fixture.process().top_frame();
  auto invk_ctx = &fixture.process().top_invocation_ctx();

  while (state.KeepRunning())
  {
    frame->push_eval_stack(oprd2);
    frame->push_eval_stack(oprd);

    corevm::runtime::instr_handler_mapfind(
      instr, fixture.process(), &frame, &invk_ctx);
  }
}

// -----------------------------------------------------------------------------

static
void BenchmarkInstrMAPAT(benchmark::State& state)
{
  InstrBenchmarksFixture fixture;

  corevm::types::NativeTypeValue oprd = corevm::types::native_map {
    { 1, 11 },
    { 2, 22 },
    { 3, 33 },
  };

  corevm::types::NativeTypeValue oprd2 =
    corevm::types::uint32(2);

  corevm::runtime::Instr instr(0, 0, 0);

  auto frame = &fixture.process().top_frame();
  auto invk_ctx = &fixture.process().top_invocation_ctx();

  while (state.KeepRunning())
  {
    frame->push_eval_stack(oprd2);
    frame->push_eval_stack(oprd);

    corevm::runtime::instr_handler_mapat(
      instr, fixture.process(), &frame, &invk_ctx);
  }
}

// -----------------------------------------------------------------------------

static
void BenchmarkInstrMAPPUT(benchmark::State& state)
{
  InstrBenchmarksFixture fixture;

  corevm::types::NativeTypeValue oprd = corevm::types::native_map {
    { 1, 11 },
    { 2, 22 },
    { 3, 33 },
  };

  corevm::types::NativeTypeValue oprd2 =
    corevm::types::uint32(2);

  corevm::types::NativeTypeValue oprd3 =
    corevm::types::uint32(222);

  corevm::runtime::Instr instr(0, 0, 0);

  auto frame = &fixture.process().top_frame();
  auto invk_ctx = &fixture.process().top_invocation_ctx();

  frame->push_eval_stack(oprd3);
  frame->push_eval_stack(oprd2);
  frame->push_eval_stack(oprd);

  while (state.KeepRunning())
  {
    corevm::runtime::instr_handler_mapput(
      instr, fixture.process(), &frame, &invk_ctx);
  }
}

// -----------------------------------------------------------------------------

static
void BenchmarkInstrMAPSET(benchmark::State& state)
{
  InstrBenchmarksFixture fixture;

  corevm::types::NativeTypeValue oprd = corevm::types::native_map {
    { 1, 11 },
    { 2, 22 },
    { 3, 33 },
  };

  corevm::runtime::variable_key_t key = 4;

  auto obj = fixture.process().create_dyobj();
  fixture.process().push_stack(obj);

  corevm::runtime::Instr instr(
    0, static_cast<corevm::runtime::instr_oprd_t>(key), 0);

  auto frame = &fixture.process().top_frame();
  auto invk_ctx = &fixture.process().top_invocation_ctx();

  while (state.KeepRunning())
  {
    frame->push_eval_stack(oprd);

    corevm::runtime::instr_handler_mapset(
      instr, fixture.process(), &frame, &invk_ctx);
  }
}

// -----------------------------------------------------------------------------

static
void BenchmarkInstrMAPERS(benchmark::State& state)
{
  InstrBenchmarksFixture fixture;

  corevm::types::NativeTypeValue oprd = corevm::types::native_map {
    { 1, 11 },
    { 2, 22 },
    { 3, 33 },
  };

  corevm::types::NativeTypeValue oprd2 =
    corevm::types::uint32(2);

  corevm::runtime::Instr instr(0, 0, 0);

  auto frame = &fixture.process().top_frame();
  auto invk_ctx = &fixture.process().top_invocation_ctx();

  while (state.KeepRunning())
  {
    frame->push_eval_stack(oprd2);
    frame->push_eval_stack(oprd);

    corevm::runtime::instr_handler_mapers(
      instr, fixture.process(), &frame, &invk_ctx);
  }
}

// -----------------------------------------------------------------------------

static
void BenchmarkInstrMAPCLR(benchmark::State& state)
{
  InstrBenchmarksFixture fixture;

  corevm::types::NativeTypeValue oprd = corevm::types::native_map {
    { 1, 11 },
    { 2, 22 },
    { 3, 33 },
  };

  corevm::runtime::Instr instr(0, 0, 0);

  auto frame = &fixture.process().top_frame();
  auto invk_ctx = &fixture.process().top_invocation_ctx();

  frame->push_eval_stack(oprd);

  while (state.KeepRunning())
  {
    corevm::runtime::instr_handler_mapclr(
      instr, fixture.process(), &frame, &invk_ctx);
  }
}

// -----------------------------------------------------------------------------

static
void BenchmarkInstrMAPSWP(benchmark::State& state)
{
  InstrBenchmarksFixture fixture;

  corevm::types::NativeTypeValue oprd = corevm::types::native_map {
    { 1, 11 },
    { 2, 22 },
    { 3, 33 },
  };

  corevm::types::NativeTypeValue oprd2 = corevm::types::native_map {
    { 11, 1 },
    { 22, 2 },
    { 33, 3 },
  };

  corevm::runtime::Instr instr(0, 0, 0);

  auto frame = &fixture.process().top_frame();
  auto invk_ctx = &fixture.process().top_invocation_ctx();

  frame->push_eval_stack(oprd);
  frame->push_eval_stack(oprd2);

  while (state.KeepRunning())
  {
    corevm::runtime::instr_handler_mapswp(
      instr, fixture.process(), &frame, &invk_ctx);
  }
}

// -----------------------------------------------------------------------------

static
void BenchmarkInstrMAPKEYS(benchmark::State& state)
{
  InstrBenchmarksFixture fixture;

  corevm::types::NativeTypeValue oprd = corevm::types::native_map {
    { 1, 11 },
    { 2, 22 },
    { 3, 33 },
  };

  corevm::runtime::Instr instr(0, 0, 0);

  auto frame = &fixture.process().top_frame();
  auto invk_ctx = &fixture.process().top_invocation_ctx();

  while (state.KeepRunning())
  {
    frame->push_eval_stack(oprd);

    corevm::runtime::instr_handler_mapkeys(
      instr, fixture.process(), &frame, &invk_ctx);
  }
}

// -----------------------------------------------------------------------------

static
void BenchmarkInstrMAPVALS(benchmark::State& state)
{
  InstrBenchmarksFixture fixture;

  corevm::types::NativeTypeValue oprd = corevm::types::native_map {
    { 1, 11 },
    { 2, 22 },
    { 3, 33 },
  };

  corevm::runtime::Instr instr(0, 0, 0);

  auto frame = &fixture.process().top_frame();
  auto invk_ctx = &fixture.process().top_invocation_ctx();

  while (state.KeepRunning())
  {
    frame->push_eval_stack(oprd);

    corevm::runtime::instr_handler_mapvals(
      instr, fixture.process(), &frame, &invk_ctx);
  }
}

// -----------------------------------------------------------------------------

#ifdef BUILD_BENCHMARKS_STRICT
static
void BenchmarkInstrMAPMRG(benchmark::State& state)
{
  InstrBenchmarksFixture fixture;

  corevm::types::NativeTypeValue oprd = corevm::types::native_map {
    { 1, 11 },
    { 2, 22 },
    { 3, 33 },
  };

  corevm::types::NativeTypeValue oprd2 = corevm::types::native_map {
    { 11, 1 },
    { 22, 2 },
    { 33, 3 },
  };

  corevm::runtime::Instr instr(0, 0, 0);

  auto frame = &fixture.process().top_frame();
  auto invk_ctx = &fixture.process().top_invocation_ctx();

  while (state.KeepRunning())
  {
    frame->push_eval_stack(oprd2);
    frame->push_eval_stack(oprd);

    corevm::runtime::instr_handler_mapmrg(
      instr, fixture.process(), &frame, &invk_ctx);
  }
}
#endif

// -----------------------------------------------------------------------------

BENCHMARK(BenchmarkInstrMAPLEN);
BENCHMARK(BenchmarkInstrMAPEMP);
BENCHMARK(BenchmarkInstrMAPFIND);
BENCHMARK(BenchmarkInstrMAPAT);
BENCHMARK(BenchmarkInstrMAPPUT);
BENCHMARK(BenchmarkInstrMAPSET);
BENCHMARK(BenchmarkInstrMAPERS);
BENCHMARK(BenchmarkInstrMAPCLR);
BENCHMARK(BenchmarkInstrMAPSWP);
BENCHMARK(BenchmarkInstrMAPKEYS);
BENCHMARK(BenchmarkInstrMAPVALS);
#ifdef BUILD_BENCHMARKS_STRICT
  BENCHMARK(BenchmarkInstrMAPMRG);
#endif

// -----------------------------------------------------------------------------
