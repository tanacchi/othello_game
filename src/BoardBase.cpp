#include "../include/BoardBase.hpp"

namespace BoardSeries
{
BoardBase::BoardBase(const Position& size)
  : board_{std::size_t(size.x * size.y)},
    size_{size},
    active_stone_{Stone::White}
{
}

inline Position::Point BoardBase::width() const
{
  return size_.x;
}

inline Position::Point BoardBase::height() const
{
  return size_.y;
}

inline Position::Point BoardBase::get_access_num(Position::Point x, Position::Point y) const
{
  return (std::size_t)(x + width()*y);
}

inline Position::Point BoardBase::get_access_num(const Position& pos) const
{
  return get_access_num(pos.x, pos.y);
}

void BoardBase::insert(Position::Point x, Position::Point y)
{
  board_[get_access_num(x, y)] = active_stone_;
}

void BoardBase::insert(Position::Point x, Position::Point y, Stone stone)
{
  board_[get_access_num(x, y)] = stone;
}
  
void BoardBase::insert(const Position& pos)
{
  insert(pos.x, pos.y);
}

void BoardBase::insert(const Position& pos, Stone stone)
{
  insert(pos.x, pos.y, stone);
}

inline bool BoardBase::is_inside(const Position& pos) const
{
  return is_inside(pos.x, pos.y);
}

inline bool BoardBase::is_inside(Position::Point x, Position::Point y) const
{
  return (0 <= x && x < width()) && (0 <= y && y < height());
}

BoardSeries::Stone BoardBase::get_enemy_stone() const
{
  return (active_stone_ == Stone::White) ? Stone::Black : Stone::White;
}

int BoardBase::get_reversible_length(const Position& pos, const Position& dr) const // REFACTORING REQUIRED
{
  const Stone enemy_stone{get_enemy_stone()};
  Position target{pos+dr};
  for (int length{0}; is_inside(target); target += dr, ++length)
    if (board_[get_access_num(target)] == active_stone_) return length;
    else if (board_[get_access_num(target)] != enemy_stone) break;
  return 0;
}

int BoardBase::count_stone(BoardSeries::Stone stone) const
{
  return std::count(std::begin(board_), std::end(board_), stone);
}

bool BoardBase::can_reverse(const Position& pos) const
{
  for (const auto& dr : direction)
    if (get_reversible_length(pos, dr) != 0) return true;
  return false;
}

void BoardBase::reverse(const Position& pos) // REFACTORING REQUIRED
{
  for (const auto& dr : direction) {
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

void show(const BoardBase& src)
{
  std::stringstream ss;
  for (int i {0}; i < src.width()+1; ++i) ss << "--";
  ss << std::endl;
  ss << "  " << std::flush;
  for (int i {0}; i < src.width(); ss.put(' '), ++i)
    ss << i+1 << std::flush;
  ss << std::endl;
  for (Position::Point y{0}; y < src.height(); ss.put('\n'), ++y) {
    ss << y+1 << ' ' << std::flush;
    for (Position::Point x {0}; x < src.width(); ss.put(' '), ++x)
      ss.put(to_char(src.board_[src.get_access_num(x, y)]));
  }
  for (int i {0}; i < src.width()+1; ++i) ss << "--";
  std::cout << ss.str() << std::endl;
}
};
