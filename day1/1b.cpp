#include <iostream>
#include <fstream>
#include <vector>

constexpr int NA = -1;

struct SlidingWindow {
  int meas1;
  int meas2;
  int meas3;
  int index;

  SlidingWindow() : meas1(NA), meas2(NA), meas3(NA), index(0) {}

  void addMeasurement(int meas) {
    if (index == 0) {
      meas1 = meas;
    }
    else if (index == 1) {
      meas2 = meas;
    }
    else if (index == 2) {
      meas3 = meas;
    }
    index = (index + 1) % 3;
  }

  void invalidate() {
    meas1 = NA;
    meas2 = NA;
    meas3 = NA;
  }

  friend bool operator> (const SlidingWindow& sw1, const SlidingWindow& sw2);
};

bool operator> (const SlidingWindow& sw1, const SlidingWindow& sw2) {
  int sum1 = sw1.meas1 + sw1.meas2 + sw1.meas3;
  int sum2 = sw2.meas1 + sw2.meas2 + sw2.meas3;

  return sum1 > sum2;
}

int main() {
  std::ifstream inputStream("./input");
  int currMeas;
  int i = 0;
  int increasesCount = 0;

  std::vector<SlidingWindow> windows {};
  windows.resize(3);

  int prevWindowIndex = 0;
  int currWindowIndex = 1;
  int nextWindowIndex = 2;

  while(inputStream >> currMeas) {
    if (i <= 2) {
      for (int j = 0; j <= i; j++) {
        windows[j].addMeasurement(currMeas);
      }
    } else {
        windows[currWindowIndex].addMeasurement(currMeas);
        if (windows[currWindowIndex] > windows[prevWindowIndex]) {
          increasesCount++;
        }
        windows[prevWindowIndex].invalidate();
        windows[prevWindowIndex].addMeasurement(currMeas);
        windows[nextWindowIndex].addMeasurement(currMeas);
        prevWindowIndex = (prevWindowIndex + 1) % 3;
        currWindowIndex = (currWindowIndex + 1) % 3;
        nextWindowIndex = (nextWindowIndex + 1) % 3;
    }
    i++;
  }

  std::cout << "Result: " << increasesCount << "\n";
}
