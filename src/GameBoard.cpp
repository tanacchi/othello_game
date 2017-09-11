#include "../include/GameBoard.hpp"

namespace BoardSeries
{
GameBoard::GameBoard(const Position size)
  : BoardBase(size)
{
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
