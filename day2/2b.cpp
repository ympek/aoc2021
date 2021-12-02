#include <iostream>
#include <fstream>

int main() {
  std::ifstream inputStream("./input");
  std::string word;
  int number;
  int horizPos = 0;
  int depth = 0;
  int aim = 0;

  while(inputStream >> word >> number) {
    if (word == "forward") {
      horizPos += number;
      depth += aim * number;
    } else if (word == "up") {
        aim -= number;
    } else if (word == "down") {
        aim += number;
    }
  }

  std::cout << "Result: " << horizPos * depth << "\n";
}
