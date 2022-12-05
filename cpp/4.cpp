#include "common.h"

namespace {
auto parse(const std::string &s) {
  auto it = std::find(s.begin(), s.end(), ',');
  std::string_view sec1{s.begin(), it};
  std::string_view sec2{std::next(it, 1), s.end()};
  std::tuple<long, long, long, long> out{};
  {
    size_t hy = sec1.find('-');
    std::from_chars(sec1.data(), sec1.data() + hy, std::get<0>(out));
    std::from_chars(sec1.data() + hy + 1, sec1.data() + sec1.size(),
                    std::get<1>(out));
  }
  {
    size_t hy = sec2.find('-');
    std::from_chars(sec2.data(), sec2.data() + hy, std::get<2>(out));
    std::from_chars(sec2.data() + hy + 1, sec2.data() + sec2.size(),
                    std::get<3>(out));
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