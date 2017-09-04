#ifndef BOARD_BASE_H_
#define BOARD_BASE_H_

#include <vector>
#include <valarray>

#include <functional>

using Point = unsigned char;
using Position = std::pair<Point, Point>;

static const std::array<std::pair<short, short>,8ul> direction {{
    {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}
  }};

class BoardBase {
public:
  enum class Stone {
    Space,
    White,
    Black,
    Dot
  };
  BoardBase(const Position size = std::make_pair(8, 8));
  BoardBase(const BoardBase& src);
  virtual ~BoardBase() = default;
  Position::first_type width() const;
  Position::second_type height() const;
  bool is_inside(Point x, Point y) const;
  bool is_inside(Position pos) const;
  std::size_t get_access_num(Position pos) const;
  std::size_t get_access_num(Point x, Point y) const;
  void insert(Point x, Point y);
  void insert(Point x, Point y, Stone&& stone);
  void insert(Position pos);
  Stone get_enemy_stone() const;
  std::size_t get_reversible_length(Position pos, std::pair<short,short>) const;
  bool can_reverse(Position pos) const;
  void reverse(Position pos);
  bool is_available_position(Position pos) const;
  void switch_active_stone();
  // for Test
  void get_size(std::size_t& width, std::size_t& height, std::size_t& length)
  {
    width = (std::size_t)size_.first;
    height = (std::size_t)size_.second;
    length = (std::size_t)board_.size();
  }
protected:
  std::valarray<Stone> board_;
  const Position size_;
  Stone active_stone_;
private:
  const BoardBase& operator=(const BoardBase& src);
};

BoardBase::BoardBase(const Position size)
  : board_{std::size_t(size.first * size.second)},
    size_{size},
    active_stone_{Stone::White}
{
}

BoardBase::BoardBase(const BoardBase& src)
  : board_{src.board_},
    size_{src.size_},
    active_stone_{src.active_stone_}
{
}

inline Position::first_type BoardBase::width() const
{
  return size_.first;
}

inline Position::second_type BoardBase::height() const
{
  return size_.second;
}

inline std::size_t BoardBase::get_access_num(Point x, Point y) const
{
  return (std::size_t)(x + width()*y);
}

inline std::size_t BoardBase::get_access_num(Position pos) const
{
  return get_access_num(pos.first, pos.second);
}

void BoardBase::insert(Point x, Point y)
{
  board_[get_access_num(x, y)] = active_stone_;
}

void BoardBase::insert(Point x, Point y, Stone&& stone)
{
  board_[get_access_num(x, y)] = stone;
}
  
void BoardBase::insert(Position pos)
{
  insert(pos.first, pos.second);
}

inline bool BoardBase::is_inside(Position pos) const
{
  return is_inside(pos.first, pos.second);
}

inline bool BoardBase::is_inside(Point x, Point y) const
{
  return x < width() && y < height();
}

BoardBase::Stone BoardBase::get_enemy_stone() const
{
  return (active_stone_ == Stone::White) ? Stone::Black : Stone::White;
}

std::size_t BoardBase::get_reversible_length(Position pos, std::pair<short,short>dr) const // REFACTORING REQUIRED
{
  Stone enemy_stone{get_enemy_stone()};
  Position target{std::make_pair(pos.first+dr.first, pos.second+dr.second)};
  for (int length{0}; is_inside(target); length++) {
    if (board_[get_access_num(target)] == active_stone_) return length;
    else if (board_[get_access_num(target)] != enemy_stone) break;
    target.first += dr.first; target.second += dr.second;
  }
  return 0;
}

bool BoardBase::can_reverse(Position pos) const
{
  for (auto dr : direction)
    if (get_reversible_length(pos, dr) != 0) return true;
  return false;
}

void BoardBase::reverse(Position pos) // REFACTORING REQUIRED
{
  for (auto dr : direction) {
    std::size_t reverse_length = get_reversible_length(pos, dr);
    for (int j{1}; j <= reverse_length; j++)
      insert(pos.first+j*dr.first, pos.second+j*dr.second);
  }
}

bool BoardBase::is_available_position(Position pos) const
{
  return is_inside(pos) && (board_[get_access_num(pos)] == Stone::Space) && can_reverse(pos);
}

void BoardBase::switch_active_stone()
{
  active_stone_ = get_enemy_stone();
}

#endif // BOARD_BASE_H_
