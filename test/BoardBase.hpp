#include <valarray>

#include <functional>

using point = unsigned char;
using position = std::pair<point, point>;

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
  BoardBase(const position size = std::make_pair(8, 8));
  BoardBase(const BoardBase& src);
  ~BoardBase() = default;
  position::first_type width() const;
  position::second_type height() const;
  bool is_inside(point x, point y) const;
  bool is_inside(position pos) const;
  std::size_t get_access_num(position pos) const;
  std::size_t get_access_num(point x, point y) const;
  void insert(point x, point y);
  void insert(point x, point y, Stone&& stone);
  void insert(position pos);
  Stone get_enemy_stone() const;
  int get_reversible_length(position pos, std::pair<short,short>) const;
  bool can_reverse(position pos) const;
  bool is_available_position(position pos) const;
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
  const position size_;
  Stone active_stone_;
private:
  const BoardBase& operator=(const BoardBase& src);
};

BoardBase::BoardBase(const position size)
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

inline position::first_type BoardBase::width() const
{
  return size_.first;
}

inline position::second_type BoardBase::height() const
{
  return size_.second;
}

inline std::size_t BoardBase::get_access_num(point x, point y) const
{
  return (std::size_t)(x + width()*y);
}

inline std::size_t BoardBase::get_access_num(position pos) const
{
  return get_access_num(pos.first, pos.second);
}

void BoardBase::insert(point x, point y)
{
  board_[get_access_num(x, y)] = active_stone_;
}

void BoardBase::insert(point x, point y, Stone&& stone)
{
  board_[get_access_num(x, y)] = active_stone_;
}
  
void BoardBase::insert(position pos)
{
  insert(pos.first, pos.second);
}

inline bool BoardBase::is_inside(position pos) const
{
  return is_inside(pos.first, pos.second);
}

inline bool BoardBase::is_inside(point x, point y) const
{
  return x < width() && y < height();
}

BoardBase::Stone BoardBase::get_enemy_stone() const
{
  return (active_stone_ == Stone::White) ? Stone::Black : Stone::White;
}

int BoardBase::get_reversible_length(position pos, std::pair<short,short>dr) const
{
  Stone enemy_stone{get_enemy_stone()};   // REFACT : もう少し賢い方法を考える
  position target{std::make_pair(pos.first+dr.first, pos.second+dr.second)};
  for (int length{0}; is_inside(target); length++) {
    if (board_[get_access_num(target)] == active_stone_) return length;
    else if (board_[get_access_num(target)] != enemy_stone) break;
    target.first += dr.first; target.second += dr.second;
  }
  return 0;
}

bool BoardBase::can_reverse(position pos) const
{
  for (auto dr : direction)
    if (get_reversible_length(pos, dr) != 0) return true;
  return false;
}

bool BoardBase::is_available_position(position pos) const
{
  return is_inside(pos) && (board_[get_access_num(pos)] == Stone::Space) && can_reverse(pos);
}

void BoardBase::switch_active_stone()
{
  active_stone_ = get_enemy_stone();
}
