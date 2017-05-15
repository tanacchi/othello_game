#include <iostream>
#include <chrono>
#include <iostream>
#include <list>
#include <random>
#include <thread>
#include <algorithm>
#include <fstream>
#include <cstdlib>

#define BOARD_SIZE 8

inline void wait(int num) { std::this_thread::sleep_for(std::chrono::milliseconds(num)); }

enum class Stone {
  SPACE,
  BLACK,
  WHITE,
  DOT
};
