#include <algorithm>
#include <bitset>
#include <cctype>
#include <charconv>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <numeric>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

using vs = std::vector<std::string>;

namespace gb::advent2021 {

// Sad state of c++ where range based iteration with split_view is just
// impossible to work in gcc 11.3
std::vector<std::string_view> split(const std::string &sentence,
                                    const std::string &delim) {
  std::vector<std::string_view> vs{};
  size_t s{0}, e{0};
  auto it = sentence.begin();
  while ((e = sentence.find(delim, s)) != std::string::npos) {
    vs.emplace_back(std::string_view{it, std::next(it, (e - s))});
    std::advance(it, (e - s) + delim.size());
    s = e + delim.size();
  }
  return vs;
}

std::vector<std::string> readIn() {
  std::vector<std::string> lines;
  for (std::string l; getline(std::cin, l);) {
    lines.emplace_back(l);
  }
  return lines;
}

void writeOut(std::string s) { std::cout << s << std::endl; }
} // namespace gb::advent2021