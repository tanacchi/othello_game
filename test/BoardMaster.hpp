#include <stdexcept>

#include "BoardBase.hpp"

class BoardMaster : private BoardBase {
public:
  BoardMaster(const position size = std::make_pair(8, 8));
  BoardMaster(const BoardMaster& src) = default;
  ~BoardMaster() = default;
  void show() const;
private:
  const BoardMaster& operator=(const BoardMaster& src);
  char to_char(BoardBase::Stone stone) const;
};

BoardMaster::BoardMaster(const position size)
  : BoardBase(size)
{
}

char BoardMaster::to_char(BoardBase::Stone stone) const
{
  switch (stone) {
  case BoardMaster::Stone::Space: return ' ';
  case BoardMaster::Stone::White: return 'O';
  case BoardMaster::Stone::Black: return 'X';
  case BoardMaster::Stone::Dot:   return '*';
  default: throw std::invalid_argument{"In to_char:Cannot convert"};
  }
  
}

void BoardMaster::show() const
{
  for (int i {0}; i < width()+1; i++) std::cout << "--";
  std::cout << std::endl;
  std::cout << "  " << std::flush;
  for (int i {0}; i < width(); std::cout.put(' '), i++)
    std::cout << i+1 << std::flush;
  std::cout << std::endl;
  for (point column {0}; column < height(); std::cout.put('\n'), column++) {
    std::cout << column+1 << ' ' << std::flush;
    for (point row {0}; row < width(); std::cout.put(' '), row++)
      std::cout.put(to_char(board_[get_access_num(row, column)]));
  }
  for (int i {0}; i < width()+1; i++) std::cout << "--";
  std::cout << std::endl;
}
