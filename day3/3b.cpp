#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include <algorithm>

constexpr int BIT_COUNT = 12;

enum RatingType {
  OXYGEN_RATING,
  CO2_RATING
};

int calculateNumberOfOnesAtColumn(std::vector<std::string>& bitsets, int columnIndex) {
  int result = 0;
  for (auto& bset : bitsets) {
    if (bset[columnIndex] == '1') {
      result++;
    }
  }
  return result;
}

int calculateRating(std::vector<std::string> bitsets, RatingType type) {
  int index = 0;

  while(true) {
    int onesInColumn = calculateNumberOfOnesAtColumn(bitsets, index);
    int zeroesInColumn = bitsets.size() - onesInColumn;
    char mostCommonBit = (onesInColumn >= zeroesInColumn) ? '1' : '0';
    auto oxygenCriteria = [=](auto bset) -> bool { return bset[index] != mostCommonBit; };

    bitsets.erase(
        std::remove_if(
          bitsets.begin(),
          bitsets.end(),
          [=](auto bset) -> bool {
            if (type == RatingType::OXYGEN_RATING) {
              return bset[index] != mostCommonBit;
            } else {
              return bset[index] == mostCommonBit;
            }
          }),
        bitsets.end());
    index++;

    if (index == BIT_COUNT || bitsets.size() == 1) {
      break;
    }
  }

  auto onlyNumberLeft = bitsets[0];
  long rating = 0;

  for (int i = 0; i < BIT_COUNT; i++) {
    int bitValue = (onlyNumberLeft[i] == '1') ? 1 : 0;
    rating |= bitValue << (BIT_COUNT - 1 - i);
  }

  return rating;
}

int main() {
  std::ifstream inputStream("./input");
  std::string bits;
  long oxygenGeneratorRating = 0;
  long co2ScrubberRating = 0;

  std::vector<std::string> bitsets;

  while(inputStream >> bits) {
    bitsets.emplace_back(bits);
  }

  oxygenGeneratorRating = calculateRating(bitsets, RatingType::OXYGEN_RATING);
  co2ScrubberRating = calculateRating(bitsets, RatingType::CO2_RATING);

  std::cout << "Result: " << oxygenGeneratorRating * co2ScrubberRating << "\n";
}
