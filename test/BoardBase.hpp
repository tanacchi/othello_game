#include <valarray>

#include <functional>

using point = unsigned char;
using position = std::pair<point, point>;

static const std::array<std::array<short,2ul>,8ul> direction_ {{
    {0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}
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
  inline position::first_type width() const;
  inline position::second_type height() const;
  inline bool is_inside(position pos) const;
  inline std::size_t get_access_num(position pos) const;
  inline std::size_t get_access_num(point x, point y) const;
  Stone get_enemy_stone() const;
  //bool is_available_position(position pos) const;
  //bool cat_reverse(position) const;
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

inline std::size_t BoardBase::get_access_num(position pos) const
{
  return get_access_num(pos.first, pos.second);
}

inline std::size_t BoardBase::get_access_num(point x, point y) const
{
  return (std::size_t)(x + width()*y);
}

inline bool BoardBase::is_inside(position pos) const
{
  return pos.first < width() && pos.first < height();
}

BoardBase::Stone BoardBase::get_enemy_stone() const
{
  return (active_stone_ == Stone::White) ? Stone::Black : Stone::White;
}

void BoardBase::switch_active_stone()
{
  active_stone_ = get_enemy_stone();
}
