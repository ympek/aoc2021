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

void printVector(std::vector<std::string>& vec) {
  for (auto& v : vec) {
    std::cout << v << ", ";
  }
  std::cout << "\n";
}

int calculateNumberOfOnesAtColumn(std::vector<std::string>& bitsets, int columnIndex) {
  int result = 0;
  for (auto& bset : bitsets) {
    if (bset[columnIndex] == '1') {
      result++;
    }
  }
  return result;
}

int calculateRating(std::vector<std::string> bitsets, std::vector<int> bitsSetInColumn, RatingType type) {
  int index = 0;

  while(true) {
    int onesInColumn = calculateNumberOfOnesAtColumn(bitsets, index);
    int zeroesInColumn = bitsets.size() - onesInColumn;
    char mostCommonBit = (onesInColumn >= zeroesInColumn) ? '1' : '0';
    std::cout << "beforeErase: idx:" << index << " onesInColumn " << onesInColumn << "/" << bitsets.size() << " and mostCommonBit is " << mostCommonBit << "\n";
    std::cout << "Note, theres " << bitsets.size() << " lines left and we're erasing...";
    // printVector(bitsets);

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

    std::cout << "after erase left: " << bitsets.size() << " lines ...";

    if (index == BIT_COUNT || bitsets.size() == 1) {
      break;
    }
  }

  auto onlyNumberLeft = bitsets[0];
  std::cout << "numberLEft: " << onlyNumberLeft << "\n";
  long rating = 0;

  for (int i = 0; i < BIT_COUNT; i++) {
    int bitValue = (onlyNumberLeft[i] == '1') ? 1 : 0;
    rating |= bitValue << (BIT_COUNT - 1 - i);
  }

  return rating;
}

int calculateCO2ScrubberRating(std::vector<std::string> bitsets, std::vector<int> bitsSetInColumn, int numLines) {
  int index = 0;

  while(true) {
    char mostCommonBit = (bitsSetInColumn[index] >= numLines/2) ? '1' : '0';
    bitsets.erase(
        std::remove_if(
          bitsets.begin(),
          bitsets.end(),
          [index, mostCommonBit](auto bset) -> bool { return bset[index] == mostCommonBit; }),
        bitsets.end());

    index++;
    if (index == BIT_COUNT || bitsets.size() == 1) {
      break;
    }
  }

  auto onlyNumberLeft = bitsets[0];
  std::cout << "numberLEft: " << onlyNumberLeft << "\n";
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
  int numLines = 0;

  std::vector<std::string> bitsets;
  std::vector<int> bitsSetInColumn(BIT_COUNT, 0);

  while(inputStream >> bits) {
    numLines++;

    for (int i = 0; i < BIT_COUNT; i++) {
      if (bits[i] == '1') {
        bitsSetInColumn.at(i)++;
      }
    }

    bitsets.emplace_back(bits);
  }

  oxygenGeneratorRating = calculateRating(bitsets, bitsSetInColumn, RatingType::OXYGEN_RATING);
  co2ScrubberRating = calculateRating(bitsets, bitsSetInColumn, RatingType::CO2_RATING);

  std::cout << "Oxygen: " << oxygenGeneratorRating << "\n";
  std::cout << "CO2: " << co2ScrubberRating << "\n";

  std::cout << "Result: " << oxygenGeneratorRating * co2ScrubberRating << "\n";
}
