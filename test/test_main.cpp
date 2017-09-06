#include <iostream>
#include "../include/GameBoard.hpp"
#include "../include/AiBoard.hpp"

int main()
{
  BoardBase::Position size{10, 10};
  GameBoard board{size};

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

  short x_buff, y_buff;
  std::cin >> x_buff;
  std::cin >> y_buff;
  PlaneVector::Point x, y;
  x = static_cast<PlaneVector::Point>(x_buff-1);
  y = static_cast<PlaneVector::Point>(y_buff-1);
  BoardBase::Position pos{x, y};
  board.insert(pos);
  board.show();

  AiBoard ai(board);
  ai.get_status_score();
  int ai_space{ai.count_stone(BoardBase::Stone::Space)};
  int ai_white{ai.count_stone(BoardBase::Stone::White)};
  int ai_black{ai.count_stone(BoardBase::Stone::Black)};

  std::cout << ai_space << std::endl;
  std::cout << ai_black << std::endl;
  std::cout << ai_white << std::endl;

  return 0;
}
