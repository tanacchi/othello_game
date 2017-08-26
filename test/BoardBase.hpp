#include <valarray>

#include <functional>

using point = unsigned char;
using position = std::pair<point, point>;
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

  void get_size(std::size_t& width, std::size_t& height, std::size_t& length)
  {
    width = (std::size_t)size_.first;
    height = (std::size_t)size_.second;
    length = (std::size_t)board_.size();
  }
private:
  const BoardBase& operator=(const BoardBase& src);
  std::valarray<Stone> board_;
  const position size_;
  Stone active_stone_;
};

BoardBase::BoardBase(const position size)
  : board_ {std::size_t(size.first * size.second)},
    size_ {size},
    active_stone_ {Stone::White}
{  
}

BoardBase::BoardBase(const BoardBase& src)
  : board_ {src.board_},
    size_ {src.size_},
    active_stone_ {src.active_stone_}
{
}

const BoardBase& BoardBase::operator=(const BoardBase& src)
{
  board_ = src.board_;
  //  size_  = src.size_;
  active_stone_ = src.active_stone_;
  return *this;
}
