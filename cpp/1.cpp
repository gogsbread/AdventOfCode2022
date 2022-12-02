#include "common.h"

namespace {
long p1(const auto &input) {
  long m{0};
  long c{0};
  for (const auto &l : input) {
    if (l.empty()) {
      m = std::max(m, c);
      c = 0;
    } else {
      c += std::atol(l.c_str());
    }
  }
  return std::max(m, c);
}

long p2(const auto &input) {
  std::vector<long> m{};
  long c{0};
  for (const auto &l : input) {
    if (l.empty()) {
      m.emplace_back(-c);
      c = 0;
    } else {
      c += std::atol(l.c_str());
    }
  }
  m.emplace_back(-c);
  std::sort(m.begin(), m.end());
  return std::abs(m[0] + m[1] + m[2]);
}
} // namespace

int main() {
  const auto &input = gb::advent2021::readIn();
  gb::advent2021::writeOut(std::to_string(p1(input)));
  gb::advent2021::writeOut(std::to_string(p2(input)));
}