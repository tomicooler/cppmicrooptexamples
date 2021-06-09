#include "helpers.h"
#include <benchmark/benchmark.h>

// https://www.agner.org/optimize/optimizing_cpp.pdf 7.13

double loop_sum(const std::vector<double> &numbers) noexcept {
  double sum{0.0};
  for (const auto num : numbers)
    sum += num;
  return sum;
}

static void BM_loop_sum(benchmark::State &state) {
  const auto numbers = random_numbers<double>(10000);

  for (auto _ : state) {
    benchmark::DoNotOptimize(loop_sum(numbers));
    benchmark::ClobberMemory();
  }
}
BENCHMARK(BM_loop_sum);

double loop_sum_stl(const std::vector<double> &numbers) noexcept {
  return std::accumulate(numbers.begin(), numbers.end(), 0.0);
}

static void BM_loop_sum_stl(benchmark::State &state) {
  const auto numbers = random_numbers<double>(10000);

  for (auto _ : state) {
    benchmark::DoNotOptimize(loop_sum_stl(numbers));
    benchmark::ClobberMemory();
  }
}
BENCHMARK(BM_loop_sum_stl);

// out of order execution and dependency chains
double loop_sum_unrolled(const std::vector<double> &numbers) noexcept {
  double t1{0}, t2{0}, t3{0}, t4{0};

  std::vector<double>::size_type i = 0;
  for (; i < numbers.size() / 4; i += 4) {
    t1 += numbers[i];
    t2 += numbers[i + 1];
    t3 += numbers[i + 2];
    t4 += numbers[i + 3];
  }
  for (; i < numbers.size(); ++i)
    t4 += numbers[i];

  return (t1 + t2) + (t3 + t4);
}

static void BM_loop_sum_unrolled(benchmark::State &state) {
  const auto numbers = random_numbers<double>(10000);

  for (auto _ : state) {
    benchmark::DoNotOptimize(loop_sum_unrolled(numbers));
    benchmark::ClobberMemory();
  }
}
BENCHMARK(BM_loop_sum_unrolled);

BENCHMARK_MAIN();
