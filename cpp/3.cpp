#include "common.h"

namespace {
long p1(const auto &input) {
  long p{0};
  for (auto l : input) {
    long m = static_cast<long>(l.length() / 2);
    auto c1 = l | std::ranges::views::take(m);
    std::ranges::sort(c1);
    auto c2 = l | std::ranges::views::drop(m);
    std::ranges::sort(c2);
    std::string s;
    std::ranges::set_intersection(c1, c2, std::back_inserter(s));
    p += (std::isupper(s[0])) ? (s[0] - '@') + 26 : (s[0] - '`');
  }
  return p;
}

long p2(auto input) {
  long p{};
  constexpr size_t sz = 3;
  for (size_t d{}; d < input.size(); d += sz) {
    auto g = input | std::ranges::views::drop(d) | std::ranges::views::take(sz);
    std::ranges::for_each(g, [](auto &gi) { std::ranges::sort(gi); });
    std::string int1{}, int2{};
    std::ranges::set_intersection(g[0], g[1], std::back_inserter(int1));
    std::ranges::set_intersection(g[2], int1, std::back_inserter(int2));
    p += (std::isupper(int2[0])) ? (int2[0] - '@') + 26 : (int2[0] - '`');
  }
  return p;
}
} // namespace

int main() {
  const auto &input = gb::advent2021::readIn();
  gb::advent2021::writeOut(std::to_string(p1(input)));
  gb::advent2021::writeOut(std::to_string(p2(input)));
}