#include <benchmark/benchmark.h>
#include <vector>

// https://youtu.be/nXaxk27zwlk?t=1112
// https://youtu.be/ZAji7PkXaKY?t=1188

static void BM_push_back(benchmark::State &state) {
  for (auto _ : state) {
    std::vector<int> v;
    v.push_back(42);
  }
}
BENCHMARK(BM_push_back);

static void BM_create(benchmark::State &state) {
  for (auto _ : state) {
    [[maybe_unused]] std::vector<int> v;
  }
}
BENCHMARK(BM_create);

static void BM_reserve(benchmark::State &state) {
  for (auto _ : state) {
    std::vector<int> v;
    v.reserve(1);
  }
}
BENCHMARK(BM_reserve);

static void BM_reserve_push_back(benchmark::State &state) {
  for (auto _ : state) {
    std::vector<int> v;
    v.reserve(1);
    v.push_back(42);
  }
}
BENCHMARK(BM_reserve_push_back);

// Add this to each function (only the create was optimized out for me)
//
// benchmark::DoNotOptimize(v);
// benchmark::ClobberMemory();

BENCHMARK_MAIN();
