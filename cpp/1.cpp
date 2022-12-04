#include "common.h"

namespace {
long p1(const auto &input) {
  long m{0};
  for (long c{}; const auto &l : input) {
    c = l.empty() ? 0 : c + std::atol(l.c_str());
    m = std::max(m, c);
  }
  return m;
}

long p2(const auto &input) {
  std::vector<long> m{0};
  for (const auto &l : input) {
    if (l.empty()) {
      m.emplace_back(0);
    } else {
      m.back() += -std::atol(l.c_str());
    }
  }
  std::sort(m.begin(), m.end());
  return std::abs(m[0] + m[1] + m[2]);
}
} // namespace

int main() {
  const auto &input = gb::advent2021::readIn();
  gb::advent2021::writeOut(std::to_string(p1(input)));
  gb::advent2021::writeOut(std::to_string(p2(input)));
}