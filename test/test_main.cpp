#include <iostream>
#include "GameBoard.hpp"

int main()
{
  GameBoard board;

  board.init();
  board.put_dots();
  board.show();
  board.remove_dots();
  board.show();
  int space{board.count_stone(BoardBase::Stone::Space)};
  int white{board.count_stone(BoardBase::Stone::White)};
  int black{board.count_stone(BoardBase::Stone::Black)};

  std::cout << space << std::endl;
  std::cout << black << std::endl;
  std::cout << white << std::endl;

  board.insert(BoardBase::Position{4, 2});
  board.show();
  board.reverse(BoardBase::Position{4, 2});
  board.show();

  return 0;
}
