#include "common.h"
#include <gmpxx.h>

// I SOLVED THE PROBLEM BUT WAS TRYING TO BE AS FUNCTIONAL AS POSSIBLE BUT.. c++
namespace {
constexpr size_t MaxSize{1024};
#define ASSERT_SCAN(expr, err)                                                 \
  if ((expr) == 0)                                                             \
    throw std::runtime_error((err));

size_t play(long &worry, auto amplify, auto pacify, int test, size_t test_true,
            size_t test_false) {
  worry = amplify(worry);
  worry = pacify(worry);
  return ((worry % test) == 0) ? test_true : test_false;
};

struct Monkey {
  decltype(play) play;
  long inspects{};
};

// parse with input
// send the mkys array
// send the items array
void parse(const auto &input, auto &mkys, auto &items) {
  using namespace std::placeholders;

  for (size_t i{0}; i < input.size(); i += 7) {
    size_t j = i / 7UL;
    auto &m = mkys[j];
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

    char c;
    long w;
    auto scans = std::sscanf(input[i + 2].c_str(),
                             "  Operation: new = old %c %d", &c, &w);
    switch (c) {
    case '+':
      auto f = std::bind(std::plus{}, w, _1);
      m.play = std::bind(play, _1, f, _2, _3, _4, _5);
      break;
    case '*':
      if (scans != 2) {
        auto f = [](long worry) { return std::multiplies{}(worry, worry); };
        m.play = std::bind(play, _1, f, _2, _3, _4, _5)
      } else {
        auto f = std::bind(std::multiplies{}, w, _1);
        m.play = std::bind(play, _1, f, _2, _3, _4, _5)
      }
    default:
      throw std::runtime_error("unknow operator " + m.op);
    }

    int t;
    size_t tt, tf;
    ASSERT_SCAN(
        std::sscanf(input[i + 3].c_str(), "  Test: divisible by %d", &t),
        "no test");
    ASSERT_SCAN(std::sscanf(input[i + 4].c_str(),
                            "    If true: throw to monkey %lu", &tt),
                "no true");
    ASSERT_SCAN(std::sscanf(input[i + 5].c_str(),
                            "    If false: throw to monkey %lu", &tf),
                "no false");
    std::bind(m.play, _1, _2, t, tt, tf);
  }
}

template <size_t N, size_t M> long p1(const auto &input) {
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
        w %= (11 * 5 * 19 * 13 * 7 * 17 * 2 * 3);
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
  gb::advent2021::writeOut(std::to_string(p1<10000, 8>(input)));
}