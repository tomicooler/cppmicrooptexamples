#ifndef CPPMICROOPTEXAMPLES_HELPERS_HH
#define CPPMICROOPTEXAMPLES_HELPERS_HH

#include <algorithm>
#include <concepts>
#include <numeric>
#include <random>
#include <vector>

template <std::floating_point T>
inline auto random_numbers(size_t size, T min = std::numeric_limits<T>::min(),
                           T max = std::numeric_limits<T>::max()) noexcept {
  static std::random_device device;
  static std::mt19937 engine{device()};
  std::uniform_real_distribution<T> distribution{min, max};

  std::vector<T> numbers(size);
  std::ranges::generate(numbers, [&]() { return distribution(engine); });
  return numbers;
}

template <std::integral T>
inline auto random_numbers(size_t size, T min = std::numeric_limits<T>::min(),
                           T max = std::numeric_limits<T>::max()) noexcept {
  static std::random_device device;
  static std::mt19937 engine{device()};
  std::uniform_int_distribution<T> distribution{min, max};

  std::vector<T> numbers(size);
  std::ranges::generate(numbers, [&]() { return distribution(engine); });
  return numbers;
}

#endif // CPPMICROOPTEXAMPLES_HELPERS_HH
