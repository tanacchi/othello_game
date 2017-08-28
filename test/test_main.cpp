#include <iostream>
#include "GameBoard.hpp"
#include "../include/BoardMaster.hpp"

int main()
{
  position p {std::make_pair(4, 4)};
  GameBoard board{p};

  std::cout << "sizeof(BoardBase) = " << sizeof(BoardBase) << ", "
            << "sizeof(GameBoard) = " << sizeof(GameBoard) << std::endl;
  std::cout << "sizeof(BoardMaster) = " << sizeof(BoardMaster) << std::endl;
  
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

  // char c = board.to_char((BoardBase::Stone)5);
  // std::cout << c << std::endl;
  board.init();
  board.show();

  // for (int i{0}; i < 10; std::cout.put('\n'), i++)
  //   for (int j{0}; j < 10; std::cout.put(' '), j++)
  //     for (int k{0}; k < 8; k++)
  //       std::cout << board.get_reversible_length(std::make_pair(j,i), direction[k]);

   // for (int i{0}; i < 10; i++)
   //   for (int j{0}; j < 10; j++)
   //     if (board.can_reverse(std::make_pair(j, i)))
   //       std::cout << "x = " << j+1 << ", y = " << i+1 << std::endl;;

  return 0;
}
