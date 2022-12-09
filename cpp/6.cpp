#include "common.h"

namespace {
long p(const auto &input, size_t m) {
  const auto &s = input[0];
  std::unordered_map<char, long> st;
  for (size_t i = 0; i < m - 1; ++i)
    st[s[i]] += 1;

  for (size_t i = m - 1; i < s.size(); ++i) {
    st[s[i]] += 1;
    if (st.size() == m)
      return i + 1;
    st[s[i - m + 1]] -= 1;
    if (!st.at(s[i - m + 1])) {
      st.erase(s[i - m + 1]);
    }
  }
  return -1;
}
} // namespace

int main() {
  const auto &input = gb::advent2021::readIn();
  gb::advent2021::writeOut(std::to_string(p(input, 4)));
  gb::advent2021::writeOut(std::to_string(p(input, 14)));
}