#include <iostream>
#include <chrono>
#include <iostream>
#include <list>
#include <random>
#include <thread>
#include <string.h>
#include <algorithm>
#include <fstream>

#define BOARD_SIZE 8
#define wait(num) std::this_thread::sleep_for(std::chrono::milliseconds(num))


enum class Stone {
  WHITE,
  BLACK,
  SPACE,
  DOT
};
