#include "common.h"

namespace {
long p1(const auto &input) {
  long out{0};
  for (auto [i, ins, inscycle, val, cy, reg] =
           std::tuple<size_t, std::string, int, long, long, long>{
               {0}, {}, {}, {}, {}, {1}};
       i < input.size(); ++i, reg += val) {
    std::istringstream ss{input[i]};
    ss >> ins >> val;
    inscycle = (ins == "addx" ? 2 : 1);
    val = (ins == "noop" ? 0 : val);
    while (inscycle--) {
      ++cy;
      if (cy <= 220 && (((cy - 20) % 40) == 0)) {
        out += (cy * reg);
      }
    }
  }
  return out;
}

void p2(const auto &input) {
  std::array<char, 40 * 6> crt{};
  for (auto [i, ins, inscycle, val, cy, px, reg] =
           std::tuple<size_t, std::string, int, long, long, long, long>{
               {0}, {}, {}, {}, {}, {}, {1}};
       i < input.size(); ++i, reg += val) {
    std::istringstream ss{input[i]};
    ss >> ins >> val;
    inscycle = (ins == "addx" ? 2 : 1);
    val = (ins == "noop" ? 0 : val);
    while (inscycle--) {
      ++cy;
      px = cy - 1;
      crt[px] = ((reg - 1 <= (px % 40)) && (reg + 1 >= (px % 40))) ? '#' : '.';
    }
  }

  for (size_t i = 0, j = 0; i < 40 * 6; ++i) {
    if ((i != 0) && (i % 40 == 0)) {
      ++j;
      std::cout << std::endl;
    }
    std::cout << crt[(j * 40) + (i % 40)];
  }
}
} // namespace

int main() {
  const auto &input = gb::advent2021::readIn();
  gb::advent2021::writeOut(std::to_string(p1(input)));
  p2(input);
}