#ifndef BOARD_BASE_H_
#define BOARD_BASE_H_

#include <algorithm>
#include <vector>
#include <valarray>
#include "PlaneVector.hpp"

#include <functional>

static const std::array<PlaneVector,8ul> direction {{
    {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}
  }};

class BoardBase {
public:
  using Position = PlaneVector;
  enum class Stone {
    Space,
    White,
    Black,
    Dot
  };
  BoardBase(const Position& size = Position{8, 8});
  const BoardBase& operator=(const BoardBase& src) = delete;
  virtual ~BoardBase() = default;
  PlaneVector::Point width() const;
  PlaneVector::Point height() const;
  bool is_inside(PlaneVector::Point x, PlaneVector::Point y) const;
  bool is_inside(const Position& pos) const;
  PlaneVector::Point get_access_num(const Position& pos) const;
  PlaneVector::Point get_access_num(PlaneVector::Point x, PlaneVector::Point y) const;
  void insert(PlaneVector::Point x, PlaneVector::Point y);
  void insert(PlaneVector::Point x, PlaneVector::Point y, Stone&& stone);
  void insert(const Position& pos);
  Stone get_enemy_stone() const;
  int get_reversible_length(Position pos, PlaneVector dr) const;
  bool can_reverse(const Position& pos) const;
  void reverse(Position pos);
  bool is_available_position(const Position& pos) const;
  void switch_active_stone();
protected:
  std::valarray<Stone> board_;
  const Position size_;
  Stone active_stone_;
private:
};

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
  Stone enemy_stone{get_enemy_stone()};
  Position target{pos+dr};
  for (int length{0}; is_inside(target); target += dr, length++) {
    if (board_[get_access_num(target)] == active_stone_) return length;
    else if (board_[get_access_num(target)] != enemy_stone) break;
  }
  return 0;
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
    std::size_t reverse_length = get_reversible_length(pos, dr);
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

#endif // BOARD_BASE_H_
