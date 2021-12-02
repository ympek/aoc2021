#include <iostream>
#include <fstream>

int main() {
  std::ifstream inputStream("./input");
  std::string word;
  int number;
  int horizPos = 0;
  int depth = 0;

  while(inputStream >> word >> number) {
    if (word == "forward") {
      horizPos += number;
    } else if (word == "up") {
      depth -= number;
    } else if (word == "down") {
      depth += number;
    }
  }
  std::cout << "Result: " << horizPos * depth << "\n";
}
