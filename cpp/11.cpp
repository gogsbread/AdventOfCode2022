#include "common.h"
#include <gmpxx.h>

namespace {
constexpr size_t MaxSize{1024};
#define ASSERT_SCAN(expr, err)                                                 \
  if ((expr) == 0)                                                             \
    throw std::runtime_error((err));

struct Monkey {
  char op;
  int wrry;
  int test;
  size_t test_true;
  size_t test_false;
  long inspects{};
};

template <size_t N, size_t M, bool p2> long p(const auto &input) {
  std::array<Monkey, M> mkys{};
  std::vector<std::tuple<size_t, long>> items{};
  for (size_t i{0}; i < input.size(); i += 7) {
    size_t j = i / 7UL;
    Monkey &m = mkys[j];
    {
      std::istringstream ss{input[i + 1]};
      std::string s, _;
      ss >> _ >> _;
      while (ss >> s) {
        if (s[s.size() - 1] == ',')
          s.resize(s.size() - 1);
        long l{};
        std::from_chars(s.data(), s.data() + s.size(), l);
        items.emplace_back(std::make_tuple(j, l));
      }
    }
    if (std::sscanf(input[i + 2].c_str(), "  Operation: new = old %c %d", &m.op,
                    &m.wrry) != 2) {
      m.op = '^';
    }
    ASSERT_SCAN(
        std::sscanf(input[i + 3].c_str(), "  Test: divisible by %d", &m.test),
        "no test");
    ASSERT_SCAN(std::sscanf(input[i + 4].c_str(),
                            "    If true: throw to monkey %lu", &m.test_true),
                "no true");
    ASSERT_SCAN(std::sscanf(input[i + 5].c_str(),
                            "    If false: throw to monkey %lu", &m.test_false),
                "no false");
  }

  for (size_t _ = 0; _ < N; ++_) {
    for (size_t i = 0; i < M; ++i) {
      auto &m = mkys[i];
      long ins{};
      for (auto &item :
           items | std::ranges::views::filter(
                       [&i](const auto &it) { return std::get<0>(it) == i; })) {
        auto &w = std::get<1>(item);
        switch (m.op) {
        case '*':
          w *= m.wrry;
          break;
        case '+':
          w += m.wrry;
          break;
        case '^':
          w *= w;
          break;
        default:
          throw std::runtime_error("unknow operator " + m.op);
        }
        if (p2) {
          w %= (11 * 5 * 19 * 13 * 7 * 17 * 2 * 3);
        } else {
          w /= 3;
        }
        const auto &tgt = ((w % m.test) == 0) ? m.test_true : m.test_false;
        std::get<0>(item) = tgt;
        ++ins;
      }
      m.inspects += ins;
    }
  }
  std::ranges::sort(mkys, std::ranges::greater(), &Monkey::inspects);
  return mkys[0].inspects * mkys[1].inspects;
}
} // namespace

int main() {
  const auto &input = gb::advent2021::readIn();
  gb::advent2021::writeOut(std::to_string(p<20, 8, false>(input)));
  gb::advent2021::writeOut(std::to_string(p<10000, 8, true>(input)));
}