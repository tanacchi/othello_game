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
  BoardBase();
  BoardBase(const BoardBase& src);
  const BoardBase& operator=(const BoardBase& src);
  ~BoardBase() = default;
private:
  std::valarray<Stone> board_;
  position size_;
};

BoardBase::BoardBase()
  : board_(4),
    size_ {std::make_pair(2, 2)}
{  
}

BoardBase::BoardBase(const BoardBase& src)
  : board_{src.board_},
    size_{src.size_}
{
}

const BoardBase& BoardBase::operator=(const BoardBase& src)
{
  board_ = src.board_;
  size_  = src.size_;
  return *this;
}
