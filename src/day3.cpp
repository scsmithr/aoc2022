#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

std::vector<std::string> ReadSacks() {
  std::string line;
  std::vector<std::string> sacks;
  while (std::getline(std::cin, line)) {
    std::string s(line);
    sacks.emplace_back(s);
  }
  return sacks;
}

int Priority(char item) {
  if (item >= 'a') {
    return (item + 1) - 'a';
  } else {
    return (item + 27) - 'A';
  }
}

std::string FindDuplicate(const std::string &sack) {
  std::string sack_copy(sack);
  auto mid = sack_copy.begin() + sack_copy.size() / 2;
  std::sort(sack_copy.begin(), mid);
  std::sort(mid, sack_copy.end());

  std::string intersect;
  std::set_intersection(sack_copy.begin(), mid, mid, sack_copy.end(),
                        std::back_inserter(intersect));
  return intersect;
}

void Part1(const std::vector<std::string> &sacks) {
  auto sum =
      std::accumulate(sacks.begin(), sacks.end(), 0, [](auto acc, auto sack) {
        return acc + Priority(FindDuplicate(sack)[0]);
      });
  std::cout << "sum: " << sum << '\n';
}

char FindBadge(std::vector<std::string> &sacks) {
  std::vector<std::array<bool, 128>> masks;
  for (auto sack : sacks) {
    std::array<bool, 128> mask;
    mask.fill(false);
    for (auto c : sack) {
      mask[c] = true;
    }
    masks.emplace_back(mask);
  }

  for (auto i = 0; i < 128; i++) {
    auto a = masks[0][i];
    auto b = masks[1][i];
    auto c = masks[2][i];
    if (a && b && c) {
      return i;
    }
  }

  return 0;
}

void Part2(const std::vector<std::string> &sacks) {
  std::vector<std::vector<std::string>> groups;
  for (auto i = 0; i < sacks.size(); i += 3) {
    std::vector<std::string> group;
    group.emplace_back(sacks[i + 0]);
    group.emplace_back(sacks[i + 1]);
    group.emplace_back(sacks[i + 2]);
    groups.emplace_back(group);
  }

  auto total = std::accumulate(groups.begin(), groups.end(), 0,
                               [](auto acc, auto sacks) {
                                 auto badge = FindBadge(sacks);
                                 return acc + Priority(badge);
                               });

  std::cout << "sum: " << total << '\n';
}

int main() {
  auto sacks = ReadSacks();
  Part1(sacks);
  Part2(sacks);
  return 0;
}
