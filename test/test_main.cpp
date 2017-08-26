#include <iostream>
#include "BoardBase.hpp"

int main()
{
  position p {std::make_pair(10, 10)};
  BoardBase board{};

  // std::size_t width, height, length;
  // board.get_size(width, height, length);
  // std::cout << width << ' ' << height << ' ' << length << std::endl;

  // std::valarray<int> a(12);
  // std::iota(std::begin(a), std::end(a), 0);
  // for (auto x : a) std::cout << x << ' ' << std::flush;
  // std::cout.put('\n');
  
  // std::valarray<int> b(13);
  // std::iota(std::begin(b), std::end(b), 100);
  // for (auto x : b) std::cout << x << ' ' << std::flush;
  // std::cout.put('\n');

  // a = b;
  // for (auto x : a) std::cout << x << ' ' << std::flush;
  // std::cout.put('\n');

  BoardBase board1{};
  BoardBase board2{board1};
  BoardBase board3{};  

  // board3 = board1;
  
  return 0;
}
