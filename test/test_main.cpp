#include <iostream>
#include "BoardBase.hpp"

int main()
{
  position p {std::make_pair(10, 10)};
  BoardBase board;

  std::size_t width, height, length;
  board.get_size(width, height, length);
  std::cout << width << ' ' << height << ' ' << length << std::endl;

  return 0;
}
