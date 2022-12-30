#include "common.h"
namespace {
struct Dir {
  std::string name;
  long size;
};

#define ASSERT_SCAN(expr, err)                                                 \
  if ((expr) == 0)                                                             \
    throw std::runtime_error((err));
constexpr size_t MaxSize{1024};

Dir solve(size_t &i, const auto &input, auto &dirs) {
  Dir d{};
  char s[MaxSize];
  ASSERT_SCAN(sscanf(input[i++].c_str(), "$ cd %s", s), "No cd");
  d.name = s;
  ASSERT_EXPR(input[i++] == "$ ls", "No ls");
  while (i < input.size() && input[i][0] != '$') {
    long sz{};
    if (input[i].find("dir") == std::string::npos)
      ASSERT_SCAN(sscanf(input[i].c_str(), "%ld ", &sz), "no file");
    d.size += sz;
    ++i;
  }
  for (bool parsing = i < input.size(); parsing;
       parsing = parsing && (i < input.size())) {
    ASSERT_SCAN(sscanf(input[i].c_str(), "$ cd %s", s), "No cd X");
    if (strcmp(s, "..") == 0) {
      ++i;
      parsing = false;
    } else {
      const auto &cd = solve(i, input, dirs);
      d.size += cd.size;
    }
  }
  dirs.emplace_back(d);
  return d;
}

long p1(const auto &input) {
  size_t i{0};
  std::vector<Dir> dirs;
  long best{0};
  solve(i, input, dirs);
  for (const Dir &d : dirs) {
    best += (d.size <= 100000) ? d.size : 0;
  }
  return best;
}

long p2(const auto &input) {
  size_t i{0};
  std::vector<Dir> dirs;
  Dir root = solve(i, input, dirs);
  long req = 30000000 - (70000000 - root.size);
  long best{root.size};
  for (Dir d : dirs) {
    if (d.size >= req)
      best = std::min(best, d.size);
  }
  return best;
}
} // namespace

int main() {
  const auto &input = gb::advent2021::readIn();
  gb::advent2021::writeOut(std::to_string(p1(input)));
  gb::advent2021::writeOut(std::to_string(p2(input)));
}