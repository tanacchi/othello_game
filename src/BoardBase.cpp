#include "../include/BoardBase.hpp"

namespace BoardSeries
{
BoardBase::BoardBase(const Position& size)
  : board_{std::size_t(size.x * size.y)},
    size_{size},
    active_stone_{Stone::White}
{
}
  
inline PlaneVector::Point BoardBase::width() const
{
  return size_.x;
}

inline PlaneVector::Point BoardBase::height() const
{
  return size_.y;
}

inline PlaneVector::Point BoardBase::get_access_num(PlaneVector::Point x, PlaneVector::Point y) const
{
  return (std::size_t)(x + width()*y);
}

inline PlaneVector::Point BoardBase::get_access_num(const Position& pos) const
{
  return get_access_num(pos.x, pos.y);
}

void BoardBase::insert(PlaneVector::Point x, PlaneVector::Point y)
{
  board_[get_access_num(x, y)] = active_stone_;
}

void BoardBase::insert(PlaneVector::Point x, PlaneVector::Point y, Stone&& stone)
{
  board_[get_access_num(x, y)] = stone;
}
  
void BoardBase::insert(const Position& pos)
{
  insert(pos.x, pos.y);
}

inline bool BoardBase::is_inside(const Position& pos) const
{
  return is_inside(pos.x, pos.y);
}

inline bool BoardBase::is_inside(PlaneVector::Point x, PlaneVector::Point y) const
{
  return (0 <= x && x < width()) && (0 <= y && y < height());
}

BoardBase::Stone BoardBase::get_enemy_stone() const
{
  return (active_stone_ == Stone::White) ? Stone::Black : Stone::White;
}

int BoardBase::get_reversible_length(Position pos, PlaneVector dr) const // REFACTORING REQUIRED // Why ref-arg rejected ?
{
  const Stone enemy_stone{get_enemy_stone()};
  Position target{pos+dr};
  for (int length{0}; is_inside(target); target += dr, length++)
    if (board_[get_access_num(target)] == active_stone_) return length;
    else if (board_[get_access_num(target)] != enemy_stone) break;
  return 0;
}

int BoardBase::count_stone(BoardBase::Stone stone) const
{
  return std::count(std::begin(board_), std::end(board_), stone);
}

bool BoardBase::can_reverse(const Position& pos) const
{
  for (auto dr : direction)
    if (get_reversible_length(pos, dr) != 0) return true;
  return false;
}

void BoardBase::reverse(Position pos) // REFACTORING REQUIRED // Why ref-arg rejected ?
{
  for (auto dr : direction) {
    int reverse_length = get_reversible_length(pos, dr);
    for (int j{1}; j <= reverse_length; j++) insert(pos+dr*j);
  }
}

bool BoardBase::is_available_position(const Position& pos) const
{
  return is_inside(pos) && (board_[get_access_num(pos)] == Stone::Space) && can_reverse(pos);
}

void BoardBase::switch_active_stone()
{
  active_stone_ = get_enemy_stone();
}
};
