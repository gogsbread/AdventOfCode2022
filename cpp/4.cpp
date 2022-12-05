#include "common.h"

namespace {
auto parse(const std::string &s) {
  auto it = std::find(s.begin(), s.end(), ',');
  std::array<std::string_view, 2> sec;
  sec[0] = std::string_view{s.begin(), it};
  sec[1] = std::string_view{std::next(it, 1), s.end()};

  std::array<long, 4> out{};
  for (size_t i = 0; const auto &sv : sec) {
    size_t hy = sv.find('-');
    std::from_chars(sv.data(), sv.data() + hy, out[i]);
    std::from_chars(sv.data() + hy + 1, sv.data() + sv.size(), out[i + 1]);
    i += 2;
  }
  return out;
}

long p1(const auto &input) {
  long c{0};
  for (const auto &l : input) {
    auto [s1b, s1e, s2b, s2e] = parse(l);
    c += ((s1b >= s2b && s1e <= s2e) || (s1b <= s2b && s1e >= s2e)) ? 1 : 0;
  }
  return c;
}

long p2(const auto &input) {
  long c{0};
  for (const auto &l : input) {
    auto [s1b, s1e, s2b, s2e] = parse(l);
    c += (s1e < s2b || s2e < s1b) ? 0 : 1;
  }
  return c;
}
} // namespace

int main() {
  const auto &input = gb::advent2021::readIn();
  gb::advent2021::writeOut(std::to_string(p1(input)));
  gb::advent2021::writeOut(std::to_string(p2(input)));
}