#include <benchmark/benchmark.h>
#include <iostream>
#include <thread>

// https://www.youtube.com/watch?v=c-hZpChQKe0&t=1763s
// memory alignment

// cat /sys/devices/system/cpu/cpu0/cache/index0/coherency_line_size
static constexpr auto CacheLineSize = 64;

struct Foo { // try this too: __attribute__((__packed__))
  char c{'x'};
  double d{0.0};
};

inline void do_work(auto &foo, double x) noexcept {
  for (int i = 0; i < 100'000; ++i)
    foo.d += x;
}

static void BM_false_sharing(benchmark::State &state) {
  Foo foo1, foo2;
  assert((reinterpret_cast<long>(&foo1) - reinterpret_cast<long>(&foo2)) !=
         CacheLineSize);

  for (auto _ : state) {
    std::thread t1{[&] { do_work(foo1, 1.0); }};
    std::thread t2{[&] { do_work(foo2, 2.0); }};
    t1.join();
    t2.join();
    benchmark::DoNotOptimize(foo1.d);
    benchmark::DoNotOptimize(foo2.d);
    benchmark::ClobberMemory();
  }
}
BENCHMARK(BM_false_sharing);

struct alignas(CacheLineSize) Foo2 {
  char c{'x'};
  double d{0.0};
};

static void BM_false_sharing_fixed(benchmark::State &state) {
  Foo2 foo1, foo2;
  assert((reinterpret_cast<long>(&foo2) - reinterpret_cast<long>(&foo1)) ==
         CacheLineSize);

  for (auto _ : state) {
    std::thread t1{[&] { do_work(foo1, 1.0); }};
    std::thread t2{[&] { do_work(foo2, 2.0); }};
    t1.join();
    t2.join();
    benchmark::DoNotOptimize(foo1.d);
    benchmark::DoNotOptimize(foo2.d);
    benchmark::ClobberMemory();
  }
}
BENCHMARK(BM_false_sharing_fixed);

BENCHMARK_MAIN();
