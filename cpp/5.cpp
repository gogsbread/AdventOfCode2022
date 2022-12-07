#include "common.h"

namespace {
struct Move {
  long qty;
  long src;
  long dst;
};

auto parse(const auto &input) {
  enum class mode { stack, move };
  mode m{mode::stack};
  std::vector<std::deque<char>> sts(10);
  std::vector<Move> mvs{};
  for (const auto &l : input) {
    if (l.empty()) {
      m = mode::move;
      continue;
    }
    if (l[1] == '1') {
      continue;
    }
    if (m == mode::stack) {
      for (size_t i = 1; i < l.size(); i += 4) {
        if (l[i] != ' ')
          sts[static_cast<int>(i / 4)].push_front(l[i]);
      }
    } else if (m == mode::move) {
      Move mv{};
      sscanf(l.c_str(), "move %ld from %ld to %ld", &mv.qty, &mv.src, &mv.dst);
      --mv.src;
      --mv.dst;
      mvs.emplace_back(std::move(mv));
    }
  }
  return std::move(make_tuple(sts, mvs));
}

std::string p1(const auto &input) {
  auto [sts, mvs] = parse(input);
  for (auto mv : mvs) {
    while (mv.qty--) {
      sts[mv.dst].push_back(sts[mv.src].back());
      sts[mv.src].pop_back();
    }
  }
  std::ostringstream out;
  for (const auto &st : sts) {
    if (st.size())
      out << st.back();
  }
  return out.str();
}

std::string p2(const auto &input) {
  auto [sts, mvs] = parse(input);
  for (auto mv : mvs) {
    std::stack<char> t;
    while (mv.qty--) {
      t.push(sts[mv.src].back());
      sts[mv.src].pop_back();
    }
    while (t.size()) {
      sts[mv.dst].push_back(t.top());
      t.pop();
    }
  }
  std::ostringstream out;
  for (const auto &st : sts) {
    if (st.size())
      out << st.back();
  }
  return out.str();
}
} // namespace

int main() {
  const auto &input = gb::advent2021::readIn();
  gb::advent2021::writeOut(p1(input));
  gb::advent2021::writeOut(p2(input));
}