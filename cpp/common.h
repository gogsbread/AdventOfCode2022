#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <numeric>
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
std::vector<std::string> readIn() {
  std::vector<std::string> lines;
  for (std::string l; getline(std::cin, l);) {
    lines.emplace_back(l);
  }
  return lines;
}

void writeOut(std::string s) { std::cout << s << std::endl; }
} // namespace gb::advent2021