#include "helpers.h"
#include <benchmark/benchmark.h>

// https://www.agner.org/optimize/optimizing_cpp.pdf 7.1
// storage types

int lookup_table_stack(int index) noexcept {
  const int table[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5,
                       6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  if (static_cast<unsigned long>(index) < sizeof(table))
    return table[index];
  return -1;
}

static void BM_lookup_table_stack(benchmark::State &state) {
  const auto numbers = random_numbers<int>(10000);

  for (auto _ : state) {
    for (const auto num : numbers) {
      benchmark::DoNotOptimize(lookup_table_stack(num & 31));
      benchmark::ClobberMemory();
    }
  }
}
BENCHMARK(BM_lookup_table_stack);

int lookup_table_global(int index) noexcept {
  static const int table[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5,
                              6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  if (static_cast<unsigned long>(index) < sizeof(table))
    return table[index];
  return -1;
}

static void BM_lookup_table_global(benchmark::State &state) {
  const auto numbers = random_numbers<int>(10000);

  for (auto _ : state) {
    for (const auto num : numbers) {
      benchmark::DoNotOptimize(lookup_table_global(num & 31));
      benchmark::ClobberMemory();
    }
  }
}
BENCHMARK(BM_lookup_table_global);

BENCHMARK_MAIN();
