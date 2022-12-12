#include "common.h"
namespace {
long p1(const auto &input) {
  std::set<std::tuple<size_t, size_t>> trees{};
  size_t m = input.size(), n = input[0].size();
  for (size_t i = 0; i < m; ++i) {
    for (auto [j, max] = std::tuple{static_cast<size_t>(0), -1}; j < n; ++j) {
      if (const auto &h = input[i][j] - '0'; h > max) {
        max = h;
        trees.emplace(std::make_tuple(i, j));
      }
    }
    for (auto [j, max] = std::tuple{n, -1}; j-- != 0;) {
      if (const auto &h = input[i][j] - '0'; h > max) {
        max = h;
        trees.emplace(std::make_tuple(i, j));
      }
    }
  }
  for (size_t j = 0; j < n; ++j) {
    for (auto [i, max] = std::tuple{static_cast<size_t>(0), -1}; i < m; ++i) {
      if (const auto &h = input[i][j] - '0'; h > max) {
        max = h;
        trees.emplace(std::make_tuple(i, j));
      }
    }
    for (auto [i, max] = std::tuple{m, -1}; i-- != 0;) {
      if (const auto &h = input[i][j] - '0'; h > max) {
        max = h;
        trees.emplace(std::make_tuple(i, j));
      }
    }
  }
  return trees.size();
}

long p2(const auto &input) {
  size_t m = input.size(), n = input[0].size();
  long best{0};
  for (size_t i = 1; i < m - 1; i++) {
    for (size_t j = 1; j < n - 1; j++) {
      long h = input[i][j] - '0';
      long l{1}, r{1}, t{1}, b{1};
      for (size_t k = static_cast<long>(j) - 1;
           k > 0 && (input[i][k] - '0') < h; --k)
        ++l;
      for (size_t k = static_cast<long>(j) + 1;
           k < n - 1 && (input[i][k] - '0') < h; ++k)
        ++r;
      for (size_t k = static_cast<long>(i) - 1;
           k > 0 && (input[k][j] - '0') < h; --k)
        ++t;
      for (size_t k = static_cast<long>(i) + 1;
           k < m - 1 && (input[k][j] - '0') < h; ++k)
        ++b;
      best = std::max(best, l * r * t * b);
    }
  }
  return best;
}
} // namespace

int main() {
  const auto &input = gb::advent2021::readIn();
  gb::advent2021::writeOut(std::to_string(p1(input)));
  gb::advent2021::writeOut(std::to_string(p2(input)));
}