#include "common.h"

namespace {
long p1(const auto &input) {
  std::unordered_map<std::string, std::string> wins{{"AY", "Y"}, {"AZ", "A"},
                                                    {"BX", "B"}, {"BZ", "Z"},
                                                    {"CX", "X"}, {"CY", "C"}};
  long s{0};
  for (const auto &l : input) {
    std::string o, p;
    std::istringstream{l} >> o >> p;
    s += p[0] - 'W';
    if (const auto &w = wins.find(o + p); w != wins.end()) {
      s += (w->second == o) ? 0 : 6;
    } else {
      s += 3;
    }
  }
  return s;
}

long p2(const auto &input) {
  std::unordered_map<std::string, int> plays{
      {"AX", 3 + 0}, {"AY", 1 + 3}, {"AZ", 2 + 6}, {"BX", 1 + 0}, {"BY", 2 + 3},
      {"BZ", 3 + 6}, {"CX", 2 + 0}, {"CY", 3 + 3}, {"CZ", 1 + 6}};
  long s{0};
  for (const auto &l : input) {
    std::string o, w;
    std::istringstream{l} >> o >> w;
    if (const auto &p = plays.at(o + w)) {
      s += p;
    }
  }
  return s;
}
} // namespace

int main() {
  const auto &input = gb::advent2021::readIn();
  gb::advent2021::writeOut(std::to_string(p1(input)));
  gb::advent2021::writeOut(std::to_string(p2(input)));
}