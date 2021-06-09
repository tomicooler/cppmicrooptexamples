#include "helpers.h"
#include <benchmark/benchmark.h>

#include <iostream>

static void BM_bad_prediction(benchmark::State &state) {
  auto numbers = random_numbers<int>(100000, 0, 5);

  for (auto _ : state) {
    long sum{0};
    for (const auto num : numbers) {
      switch (num) {
      case 0:
        sum -= 5;
        break;
      case 1:
        sum += 1;
        break;
      case 2:
        sum -= 1;
        break;
      case 3:
        sum += 2;
        break;
      case 4:
        sum -= 2;
        break;
      case 5:
        sum -= 5;
        break;
      }
    }
    benchmark::DoNotOptimize(sum);
    benchmark::ClobberMemory();
  }
}
BENCHMARK(BM_bad_prediction);

static void BM_good_prediction(benchmark::State &state) {
  auto numbers = random_numbers<int>(100000, 0, 5);
  std::sort(numbers.begin(), numbers.end());

  for (auto _ : state) {
    long sum{0};
    for (const auto num : numbers) {
      switch (num) {
      case 0:
        sum -= 5;
        break;
      case 1:
        sum += 1;
        break;
      case 2:
        sum -= 1;
        break;
      case 3:
        sum += 2;
        break;
      case 4:
        sum -= 2;
        break;
      case 5:
        sum -= 5;
        break;
      }
    }
    benchmark::DoNotOptimize(sum);
    benchmark::ClobberMemory();
  }
}
BENCHMARK(BM_good_prediction);

static void BM_lookup_table(benchmark::State &state) {
  auto numbers = random_numbers<int>(100000, 0, 5);

  static const int lookup[] = {-5, 1, -1, 2, -2, 5};

  for (auto _ : state) {
    long sum{0};
    for (const auto num : numbers) {
      sum += lookup[num];
    }
    benchmark::DoNotOptimize(sum);
    benchmark::ClobberMemory();
  }
}
BENCHMARK(BM_lookup_table);

BENCHMARK_MAIN();
