#include "common.h"

namespace {
using Pos = std::complex<long>;

template <size_t N> long p1(const auto &input) {
  auto Hasher = [](const Pos &k) -> std::size_t {
    return std::hash<long>()(k.real()) ^ std::hash<long>()(k.imag());
  };
  auto offset = [](const Pos &p) {
    return Pos{(std::abs(p.real()) >= 2 ? p.real() / 2L : p.real()),
               (std::abs(p.imag()) >= 2 ? p.imag() / 2L : p.imag())};
  };
  std::unordered_set<Pos, decltype(Hasher)> v{Pos{0, 0}};
  std::array<Pos, N> rope{};
  std::unordered_map<char, Pos> dir{
      {'R', Pos{1, 0}}, {'L', Pos{-1, 0}}, {'U', Pos{0, 1}}, {'D', Pos{0, -1}}};
  for (auto [d, l, prev] = std::tuple{' ', 0L, Pos{0, 0}};
       const auto &s : input) {
    std::istringstream ss{s};
    ss >> d >> l;
    while (l--) {
      rope[0] += dir[d];
      for (const auto i : std::ranges::views::iota(1UL, N)) {
        const auto diff = rope[i - 1] - rope[i];
        if (std::abs(diff) >= 2)
          rope[i] += offset(diff);
      }
      v.emplace(rope[N - 1]);
    }
  }
  return v.size();
}
} // namespace

int main() {
  const auto &input = gb::advent2021::readIn();
  gb::advent2021::writeOut(std::to_string(p1<2>(input)));
  gb::advent2021::writeOut(std::to_string(p1<10>(input)));
}