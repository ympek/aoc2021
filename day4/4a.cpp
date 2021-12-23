#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include <algorithm>

constexpr int NUMBERS_PER_BOARD = 25;

void splitString(std::string str, std::vector<int>& outputVector, std::string delim = ",")
{
  std::cout << "PARSING>>>>>\n";
  size_t pos = 0;
  std::string token;

  while((pos = str.find(delim)) != std::string::npos)
  {
    token = str.substr(0, pos);
    std::cout << "token: " << token << " stoiToken: " << std::stoi(token) << " pos: " << pos << "\n";
    outputVector.push_back(std::stoi(token));
    str.erase(0, pos + delim.length());
    std::cout << "str after erase:\n" << str << "\n";
  }
  // don't forget last element
  outputVector.push_back(std::stoi(str));
}

class Board {
public:
  Board() {}

  void add(int num) {
    if (!isComplete()) {
      numbers.push_back(num);
    }
  }

  void mark(int numberToMark) {
    for (int i = 0; i < numbers.size(); i++) {
      if (numbers[i] == numberToMark) {
        marks.set(i);
      }
    }
  }

  bool isWinning() {
    // sprawdzamy marki
    std::vector<std::bitset<NUMBERS_PER_BOARD>> masks {
      // poziomy
      0b0000000000000000000011111,
      0b0000000000000001111100000,
      0b0000000000111110000000000,
      0b0000011111000000000000000,
      0b1111100000000000000000000,
      // piony
      0b0000100001000010000100001,
      0b0001000010000100001000010,
      0b0010000100001000010000100,
      0b0100001000010000100001000,
      0b1000010000100001000010000,
    };

    for (auto& mask : masks) {
      if ((marks & mask) == mask) {
        return true;
      }
    }
    return false;
  }

  int sumUnmarked() {
    int sum = 0;
    for (int i = 0; i < numbers.size(); i++) {
      if(!marks.test(i)) {
        sum += numbers[i];
      }
    }
    return sum;
  }

  bool isComplete() {
    return (numbers.size() == NUMBERS_PER_BOARD);
  }

  void print() {
    for (int i = 0; i < numbers.size(); i++) {
      if (i % 5 == 0) {
        std::cout << "\n";
      }
      if (marks.test(i)) {
        std::cout << " [" << numbers[i] << "] ";
      } else {
        std::cout << " " << numbers[i] << " ";
      }
    }
  }

private:
  int ptr;
  // board will hold BOARD_SIZE * BOARD_SIZE numbers;
  std::vector<int> numbers;
  std::bitset<NUMBERS_PER_BOARD> marks;
};

int main() {
  std::ifstream inputStream("./input");
  std::string chunk;
  long gammaRate = 0;
  long epsilonRate = 0;
  int numLines = 0;

  std::vector<int> drawnNumbers;

  std::vector<Board> boards;

  int iteration = 0;
  int currentBoardIndex = 0;
  Board* currentBoard = 0;

  while(inputStream >> chunk) {
    // first chunk is drawn numbers, split it.
    if (iteration == 0) {
      splitString(chunk, drawnNumbers);
      iteration++;
      continue;
    }

    if (iteration % NUMBERS_PER_BOARD == 1) {
      currentBoardIndex = boards.size();
      boards.resize(currentBoardIndex + 1);
    }

    boards[currentBoardIndex].add(std::stoi(chunk));

    iteration++;
  }

  int result = 0;
  bool hasResult = false;

  // ok now we parsed data, duh
  for (int luckyNumber : drawnNumbers) {
    // drawing a number
    std::cout << "Drawing a number: " << luckyNumber << "\n";

    std::for_each(boards.begin(), boards.end(), [&](Board& b) {
      b.mark(luckyNumber);
      if (b.isWinning() && !hasResult) {
        std::cout << "WINNER IS THERE=================================\n";
        hasResult = true;
        int sumOfUnmarked = b.sumUnmarked();
        result = sumOfUnmarked * luckyNumber;
      }
      std::cout << "\n";
      b.print();
      std::cout << "\n";
    });
    if (hasResult) {
      std::cout << "Lucky number was " << luckyNumber;
      break;
    }
  }

  std::cout << "\nResult: " << result << "\n";
}
