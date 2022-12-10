#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

std::vector<int> ReadCalories() {
  std::string line;
  std::vector<int> calories;
  int curr_cals = 0;
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      calories.emplace_back(curr_cals);
      curr_cals = 0;
    } else {
      curr_cals += std::stoi(line);
    }
  }
  return calories;
}

void Part1(std::vector<int> const &calories) {
  std::cout << "max: " << *std::max_element(calories.begin(), calories.end())
            << '\n';
}

void Part2(std::vector<int> &calories) {
  std::sort(calories.begin(), calories.end(), std::greater<>());
  int sum = 0;
  for (int i = 0; i < 3; i++) {
    sum += calories[i];
  }
  std::cout << "sum: " << sum << '\n';
}

int main() {
  auto calories = ReadCalories();
  Part1(calories);
  Part2(calories);
}
