#include "helpers.h"
#include <benchmark/benchmark.h>

// https://www.agner.org/optimize/optimizing_cpp.pdf 7.11

// signed -> unsigned : 0 cycle
unsigned int signed_to_unsigned(int num) noexcept { return num; }

// unsigned -> signed : 0 cycle
int unsigned_to_signed(unsigned int num) noexcept { return num; }

// int -> short : 1 cycle if the source is arithmetic otherwise 0
short int_to_short(int num) noexcept { return num; }

// short -> int : 0 cycle
int short_to_int(short num) noexcept { return num; }

// double -> float: 0 cycle when floating point register stack is used otherwise
// (xmm) 2-15 cycles
float double_to_float(double num) noexcept { return num; }

// float -> double : 0 cycle when floating point register stack is used
// otherwise (xmm) 2-15 cycles
double float_to_double(float num) noexcept { return num; }

// signed int -> float : 4-6 cycles
float int_to_float(int num) noexcept { return num; }

// unsigned int -> float : takes longer then signed unless AVX512 is used
float unsigned_int_to_float(unsigned int num) noexcept { return num; }

float unsigned_int_to_float_faster(unsigned int num) noexcept {
  return static_cast<int>(num);
}

// float -> int : long unless SSE2 is used (50-100 cycles)
int float_to_int(float num) noexcept { return num; }

// ### BENCHMARKS ###

static void BM_just_loop(benchmark::State &state) {
  const auto numbers = random_numbers<int>(1000);

  for (auto _ : state) {
    for (const auto num : numbers) {
      benchmark::DoNotOptimize(num);
      benchmark::ClobberMemory();
    }
  }
}
BENCHMARK(BM_just_loop);

static void BM_signed_unsigned(benchmark::State &state) {
  const auto numbers = random_numbers<int>(1000);

  for (auto _ : state) {
    for (const auto num : numbers) {
      benchmark::DoNotOptimize(signed_to_unsigned(num));
      benchmark::ClobberMemory();
    }
  }
}
BENCHMARK(BM_signed_unsigned);

static void BM_unsigned_signed(benchmark::State &state) {
  const auto numbers = random_numbers<unsigned int>(1000);

  for (auto _ : state) {
    for (const auto num : numbers) {
      benchmark::DoNotOptimize(unsigned_to_signed(num));
      benchmark::ClobberMemory();
    }
  }
}
BENCHMARK(BM_unsigned_signed);

static void BM_int_to_short(benchmark::State &state) {
  const auto numbers = random_numbers<int>(1000);

  for (auto _ : state) {
    for (const auto num : numbers) {
      benchmark::DoNotOptimize(int_to_short(num));
      benchmark::ClobberMemory();
    }
  }
}
BENCHMARK(BM_int_to_short);

static void BM_short_to_int(benchmark::State &state) {
  const auto numbers = random_numbers<short>(1000);

  for (auto _ : state) {
    for (const auto num : numbers) {
      benchmark::DoNotOptimize(short_to_int(num));
      benchmark::ClobberMemory();
    }
  }
}
BENCHMARK(BM_short_to_int);

static void BM_double_to_float(benchmark::State &state) {
  const auto numbers = random_numbers<double>(1000);

  for (auto _ : state) {
    for (const auto num : numbers) {
      benchmark::DoNotOptimize(double_to_float(num));
      benchmark::ClobberMemory();
    }
  }
}
BENCHMARK(BM_double_to_float);

static void BM_float_to_double(benchmark::State &state) {
  const auto numbers = random_numbers<float>(1000);

  for (auto _ : state) {
    for (const auto num : numbers) {
      benchmark::DoNotOptimize(float_to_double(num));
      benchmark::ClobberMemory();
    }
  }
}
BENCHMARK(BM_float_to_double);

static void BM_int_to_float(benchmark::State &state) {
  const auto numbers = random_numbers<int>(1000);

  for (auto _ : state) {
    for (const auto num : numbers) {
      benchmark::DoNotOptimize(int_to_float(num));
      benchmark::ClobberMemory();
    }
  }
}
BENCHMARK(BM_int_to_float);

static void BM_unsigned_to_float(benchmark::State &state) {
  const auto numbers = random_numbers<unsigned int>(1000);

  for (auto _ : state) {
    for (const auto num : numbers) {
      benchmark::DoNotOptimize(unsigned_int_to_float(num));
      benchmark::ClobberMemory();
    }
  }
}
BENCHMARK(BM_unsigned_to_float);

static void BM_unsigned_to_float_faster(benchmark::State &state) {
  const auto numbers = random_numbers<unsigned int>(1000);

  for (auto _ : state) {
    for (const auto num : numbers) {
      benchmark::DoNotOptimize(unsigned_int_to_float_faster(num));
      benchmark::ClobberMemory();
    }
  }
}
BENCHMARK(BM_unsigned_to_float_faster);

static void BM_float_to_int(benchmark::State &state) {
  const auto numbers = random_numbers<float>(1000);

  for (auto _ : state) {
    for (const auto num : numbers) {
      benchmark::DoNotOptimize(float_to_int(num));
      benchmark::ClobberMemory();
    }
  }
}
BENCHMARK(BM_float_to_int);

BENCHMARK_MAIN();
