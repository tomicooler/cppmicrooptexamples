#include "helpers.h"
#include <array>
#include <benchmark/benchmark.h>
#include <numeric>
#include <vector>

static constexpr int COL_SIZE = 1000;
static constexpr int ROW_SIZE = 1000;
using Array2D = std::array<std::array<int, ROW_SIZE>, COL_SIZE>;

static void BM_by_row(benchmark::State &state) {
  Array2D matrix;
  for (auto &row : matrix)
    std::iota(row.begin(), row.end(), 0);

  for (auto _ : state) {
    for (Array2D::size_type i = 0; i < matrix.size(); ++i) {
      for (Array2D::size_type j = 0; j < matrix.at(i).size(); ++j) {
        benchmark::DoNotOptimize(matrix.at(i).at(j));
        benchmark::ClobberMemory();
      }
    }
  }
}
BENCHMARK(BM_by_row);

static void BM_by_column(benchmark::State &state) {
  Array2D matrix;
  for (auto &row : matrix)
    std::iota(row.begin(), row.end(), 0);

  for (auto _ : state) {
    for (Array2D::size_type i = 0; i < matrix.size(); ++i) {
      for (Array2D::size_type j = 0; j < matrix.at(i).size(); ++j) {
        benchmark::DoNotOptimize(matrix.at(j).at(i));
        benchmark::ClobberMemory();
      }
    }
  }
}
BENCHMARK(BM_by_column);

// https://www.youtube.com/watch?v=2EWejmkKlxs&t=452s
static void BM_cache_size(benchmark::State &state) {
  const int bytes = 1 << state.range(0);
  const int count = (bytes / sizeof(int)) / 2;
  const auto numbers = random_numbers<int>(count);
  const auto indicies = random_numbers<int>(count, 0, count);

  for (auto _ : state) {
    long sum{0};
    for (const auto index : indicies) {
      sum += numbers[index];
    }
    benchmark::DoNotOptimize(sum);
    benchmark::ClobberMemory();
  }

  state.SetBytesProcessed(state.iterations() * bytes);
  state.SetLabel(std::to_string(bytes / 1024) + "kb");
}
BENCHMARK(BM_cache_size)->DenseRange(13, 26)->ReportAggregatesOnly(true);

BENCHMARK_MAIN();
