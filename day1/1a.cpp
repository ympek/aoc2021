#include <iostream>
#include <fstream>

int main() {
  std::ifstream inputStream("./input");
  int currDepthMeasurement, prevDepthMeasurement;
  int i = 0;
  int increasesCount = 0;
  while(inputStream >> currDepthMeasurement) {
    if (i != 0 && currDepthMeasurement > prevDepthMeasurement) {
      increasesCount++;
    }
    prevDepthMeasurement = currDepthMeasurement;
    i++;
  }

  std::cout << "Result: " << increasesCount << "\n";
}
