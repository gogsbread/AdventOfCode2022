#include "common.h"

namespace {
struct Packet;
using Packets = std::vector<Packet>;
struct Packet {
  std::variant<int, Packets> d;
};

Packet _parse(const std::string &str, size_t &begin) {
  Packets pkts{};
  while (str[begin] != ']') {
    if (str[begin] == '[') {
      pkts.emplace_back(_parse(str, ++begin));
    } else if (str[begin] == ',') {
      ++begin;
    } else {
      int i;
      std::istringstream ss{str};
      ss.seekg(begin, std::ios_base::beg);
      ss >> i;
      pkts.emplace_back(i);
      begin = ss.tellg();
    }
  }
  ++begin;
  return Packet{pkts};
}

Packet parse(const std::string &str) {
  size_t s{1};
  return _parse(str, s);
}

int compare(const Packet &p1, const Packet &p2) {
  if (std::holds_alternative<Packets>(p1.d) &&
      std::holds_alternative<Packets>(p2.d)) {
    const auto &pkts1 = std::get<Packets>(p1.d);
    const auto &pkts2 = std::get<Packets>(p2.d);
    size_t i{0}, j{0};
    for (; i < pkts1.size() && j < pkts2.size(); ++i, ++j) {
      if (int r{}; (r = compare(pkts1[i], pkts2[j])) != 0)
        return r;
    }
    return compare(Packet{static_cast<int>(pkts1.size() - i)},
                   Packet{static_cast<int>(pkts2.size() - j)});
  } else if (std::holds_alternative<Packets>(p1.d)) {
    return compare(p1, Packet{Packets{p2}});
  } else if (std::holds_alternative<Packets>(p2.d)) {
    return compare(Packet{Packets{p1}}, p2);
  }
  ASSERT_EXPR(std::holds_alternative<int>(p1.d), "p1 not int");
  ASSERT_EXPR(std::holds_alternative<int>(p2.d), "p2 not int");
  return (std::get<int>(p1.d) < std::get<int>(p2.d)) -
         (std::get<int>(p2.d) < std::get<int>(p1.d));
}

long p1(const auto &input) {
  long res{0};
  for (size_t i{0}; i < input.size(); i += 3) {
    const auto &pkt1 = parse(input[i]);
    const auto &pkt2 = parse(input[i + 1]);
    res += (compare(pkt1, pkt2) > 0) ? ((i / 3) + 1) : 0;
  }
  return res;
}

long p2(auto input) {
  input.emplace_back("[[2]]");
  input.emplace_back("[[6]]");
  auto comparer = [](std::string &a, std::string &b) {
    const auto &p1 = parse(a);
    const auto &p2 = parse(b);
    return compare(p1, p2) > 0;
  };
  std::vector<std::string> pkts;
  std::ranges::for_each(
      input | std::ranges::views::filter(
                  [](const std::string &s) { return !s.empty(); }),
      [&pkts](const auto &pkt) { pkts.emplace_back(pkt); });
  std::ranges::sort(
      pkts,
      comparer); // one cannot simply sort the ouput of `views::filter` because
                 // the `ranges::sort` requires a random access iterator whereas
                 // the `filter` only produces a forward iterator
  size_t i = (std::ranges::find(pkts, "[[2]]") - pkts.begin()) + 1;
  size_t j = (std::ranges::find(pkts, "[[6]]") - pkts.begin()) + 1;
  return i * j;
}
} // namespace

int main() {
  const auto &input = gb::advent2021::readIn();
  gb::advent2021::writeOut(std::to_string(p1(input)));
  gb::advent2021::writeOut(std::to_string(p2(input)));
}