#include <atomic>
#include <benchmark/benchmark.h>
#include <iostream>
#include <new>
#include <thread>

// https://www.youtube.com/watch?v=c-hZpChQKe0&t=1763s

// https://en.cppreference.com/w/cpp/thread/hardware_destructive_interference_size
#ifdef __cpp_lib_hardware_interference_size
using std::hardware_constructive_interference_size;
using std::hardware_destructive_interference_size;
#else
constexpr std::size_t hardware_constructive_interference_size =
    2 * sizeof(std::max_align_t);
constexpr std::size_t hardware_destructive_interference_size =
    2 * sizeof(std::max_align_t);
#endif

struct alignas(hardware_constructive_interference_size) Foo {
  std::atomic_uint64_t x{};
  std::atomic_uint64_t y{};
};

inline void do_work_x(auto &foo) noexcept {
  for (int i = 0; i < 100'000; ++i)
    foo.x.fetch_add(1, std::memory_order_relaxed);
}

inline void do_work_y(auto &foo) noexcept {
  for (int i = 0; i < 100'000; ++i)
    foo.y.fetch_add(-1, std::memory_order_relaxed);
}

static void BM_false_sharing(benchmark::State &state) {
  Foo foo;

  for (auto _ : state) {
    std::thread t1{[&] { do_work_x(foo); }};
    std::thread t2{[&] { do_work_y(foo); }};
    t1.join();
    t2.join();
    benchmark::DoNotOptimize(foo.x);
    benchmark::DoNotOptimize(foo.y);
    benchmark::ClobberMemory();
  }
}
BENCHMARK(BM_false_sharing);

struct Foo2 {
  alignas(hardware_destructive_interference_size) std::atomic_uint64_t x{};
  alignas(hardware_destructive_interference_size) std::atomic_uint64_t y{};
};

static void BM_false_sharing_fixed(benchmark::State &state) {
  Foo2 foo;

  for (auto _ : state) {
    std::thread t1{[&] { do_work_x(foo); }};
    std::thread t2{[&] { do_work_y(foo); }};
    t1.join();
    t2.join();
    benchmark::DoNotOptimize(foo.x);
    benchmark::DoNotOptimize(foo.y);
    benchmark::ClobberMemory();
  }
}
BENCHMARK(BM_false_sharing_fixed);

BENCHMARK_MAIN();
