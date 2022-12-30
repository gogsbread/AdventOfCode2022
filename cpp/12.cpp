#include "common.h"

namespace {
#define NOT_FOUND -1
using Pos = std::complex<size_t>;
using Heading = std::complex<long>;

long solve(const auto &input, Pos st, Pos end) {
  size_t m = input.size(), n = input[0].size();

  auto hasher = [](const Pos &k) -> std::size_t {
    return std::hash<long>()(k.real()) ^ std::hash<long>()(k.imag());
  };
  auto within_bounds = [&m, &n](const Heading &v) -> bool {
    return v.imag() >= 0 && v.real() >= 0 && v.imag() < static_cast<long>(n) &&
           v.real() < static_cast<long>(m);
  };
  auto within_height = [&input](const Pos &u, const Heading &v) -> bool {
    return (input[v.real()][v.imag()] - input[u.real()][u.imag()] <= 1);
  };
  std::array<Heading, 4> dirs = {Heading{-1, 0}, Heading{1, 0}, Heading{0, -1},
                                 Heading{0, 1}};
  std::deque<std::tuple<Pos, long>> frontier{{st, 0}};
  std::unordered_set<Pos, decltype(hasher)> visited{st};
  long res{NOT_FOUND};
  while (frontier.size() > 0 && res == NOT_FOUND) {
    const auto &[u, d] = frontier.front();
    if (u == end) {
      res = d;
      continue;
    }
    for (const auto &dir : dirs) {
      Heading v = dir + static_cast<Heading>(u);
      if (!visited.contains(static_cast<Pos>(v)) && within_bounds(v) &&
          within_height(u, v)) {
        frontier.push_back({v, d + 1});
        visited.emplace(v);
      }
    }
    frontier.pop_front();
  }
  return res;
}

long p1(auto input) {
  Pos st{}, end{};
  for (size_t i{0}; const auto &line : input) {
    if (size_t j{0}; (j = line.find("S")) != std::string::npos)
      st = Pos{i, j};
    if (size_t j{0}; (j = line.find("E")) != std::string::npos)
      end = Pos{i, j};
    ++i;
  }
  input[st.real()][st.imag()] = 'a';
  input[end.real()][end.imag()] = 'z';

  const auto res = solve(input, st, end);
  ASSERT_EXPR(res != NOT_FOUND, "Failed to find solution");
  return res;
}

long p2(auto input) {
  size_t m = input.size(), n = input[0].size();

  std::vector<Pos> strts{};
  Pos end{};
  for (size_t i{0}; i < m; ++i) {
    for (size_t j{0}; j < n; ++j) {
      if (input[i][j] == 'a' || input[i][j] == 'S') {
        strts.emplace_back(Pos{i, j});
        input[i][j] = 'a';
      }
      if (input[i][j] == 'E') {
        end = Pos{i, j};
        input[i][j] = 'z';
      }
    }
  }

  std::vector<long> res{};
  for (const auto &st : strts) {
    const auto t = solve(input, st, end);
    if (t != NOT_FOUND)
      res.emplace_back(t);
  }
  ASSERT_EXPR(res.size() != 0, "Failed to find solution");
  return std::ranges::min(res);
}
} // namespace

int main() {
  const auto &input = gb::advent2021::readIn();
  gb::advent2021::writeOut(std::to_string(p1(input)));
  gb::advent2021::writeOut(std::to_string(p2(input)));
}