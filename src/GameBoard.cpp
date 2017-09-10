#include "../include/GameBoard.hpp"

namespace BoardSeries
{
GameBoard::GameBoard(const Position size)
  : BoardBase(size)
{
}

char to_char(Stone stone)
{
  switch (stone) {
  case Stone::Space: return ' ';
  case Stone::White: return 'O';
  case Stone::Black: return 'X';
  case Stone::Dot:   return '*';
  default: throw std::invalid_argument{"In to_char:Cannot convert"};
  }  
}

void GameBoard::show() const
{
  for (int i {0}; i < width()+1; i++) std::cout << "--";
  std::cout << std::endl;
  std::cout << "  " << std::flush;
  for (int i {0}; i < width(); std::cout.put(' '), i++)
    std::cout << i+1 << std::flush;
  std::cout << std::endl;
  for (PlaneVector::Point column {0}; column < height(); std::cout.put('\n'), column++) {
    std::cout << column+1 << ' ' << std::flush;
    for (PlaneVector::Point row {0}; row < width(); std::cout.put(' '), row++)
      std::cout.put(to_char(board_[get_access_num(row, column)]));
  }
  for (int i {0}; i < width()+1; i++) std::cout << "--";
  std::cout << std::endl;
}

void GameBoard::init()
{
  board_ = Stone::Space;
  board_[std::slice(get_access_num(width()/2-1, height()/2-1), 2, width()+1)] = Stone::White;
  board_[std::slice(get_access_num(width()/2  , height()/2-1), 2, width()-1)] = Stone::Black;
}

Stone GameBoard::get_active_stone() const
{
  return active_stone_;
}

bool GameBoard::can_continue() const // 「両方打つとこ無し」も調べたいx
{
  return std::any_of(std::begin(board_), std::end(board_), [](Stone target){ return target == Stone::Space; });
}

void GameBoard::put_dots()
{
  Position elem{0, 0};
  for (elem.x = 0; elem.x < width(); ++elem.x)
    for (elem.y = 0; elem.y < height(); ++elem.y)
      if (is_available_position(elem)) board_[get_access_num(elem)] = Stone::Dot;
}

void GameBoard::remove_dots()
{
  std::replace_if(std::begin(board_), std::end(board_), [](Stone target){ return target == Stone::Dot; }, Stone::Space);
}
};
