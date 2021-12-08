#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>

int main() {
  std::ifstream inputStream("./input");
  std::string bits;
  long gammaRate = 0;
  long epsilonRate = 0;
  int numLines = 0;

  std::vector<int> bitsSetInColumn(12, 0);

  while(inputStream >> bits) {
    numLines++;

    for (int i = 0; i < 12; i++) {
      if (bits[i] == '1') {
        bitsSetInColumn.at(i)++;
      }
    }
  }

  for (int i = 0; i < 12; i++) {
    if (bitsSetInColumn[i] > numLines/2) {
      gammaRate |= 1 << (11 - i);
    } else {
      epsilonRate |= 1 << (11 - i);
    }
  }

  std::cout << "Result: " << gammaRate * epsilonRate << "\n";
}
