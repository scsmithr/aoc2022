#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

std::vector<std::pair<int, int>> ReadGuide() {
  std::vector<std::pair<int, int>> guide;
  char opp, me;
  while (std::cin >> opp >> me) {
    auto pair = std::make_pair(opp - 'A', me - 'X');
    guide.emplace_back(pair);
  }
  return guide;
}

int Score(const std::pair<int, int> &round) {
  if (round.first == round.second) {
    return 3;
  }
  if (round.first == (round.second + 1) % 3) {
    return 0;
  }
  return 6;
}

int TotalScore(const std::vector<std::pair<int, int>> &guide) {
  auto accumulator = [](auto acc, auto pair) {
    return acc + Score(pair) + pair.second + 1;
  };
  auto total = std::accumulate(guide.begin(), guide.end(), 0, accumulator);
  return total;
}

void Part1(const std::vector<std::pair<int, int>> &guide) {
  std::cout << "total: " << TotalScore(guide) << '\n';
}

void Part2(std::vector<std::pair<int, int>> &guide) {
  std::vector<std::pair<int, int>> new_guide;
  std::transform(guide.begin(), guide.end(), std::back_inserter(new_guide),
                 [](auto round) {
                   auto new_pair = std::make_pair(
                       round.first, (round.first + round.second + 2) % 3);
                   return new_pair;
                 });
  auto total = TotalScore(new_guide);
  std::cout << "total: " << total << '\n';
}

int main() {
  auto guide = ReadGuide();
  Part1(guide);
  Part2(guide);
}
