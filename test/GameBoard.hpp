#include <stdexcept>

#include "BoardBase.hpp"

class GameBoard : private BoardBase {
public:
  GameBoard(const position size = std::make_pair(8, 8));
  GameBoard(const GameBoard& src) = default;
  ~GameBoard() = default;
  void show() const;
  void init();
  bool can_continue() const;
private:
  const GameBoard& operator=(const GameBoard& src);
  char to_char(BoardBase::Stone stone) const;
};

GameBoard::GameBoard(const position size)
  : BoardBase(size)
{
}

char GameBoard::to_char(BoardBase::Stone stone) const
{
  switch (stone) {
  case BoardBase::Stone::Space: return ' ';
  case BoardBase::Stone::White: return 'O';
  case BoardBase::Stone::Black: return 'X';
  case BoardBase::Stone::Dot:   return '*';
  default: throw std::invalid_argument{"In to_char:Cannot convert"};
  }  
}

void GameBoard::show() const
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

void GameBoard::init()
{
  board_ = Stone::Space;
  board_[std::slice(get_access_num(width()/2-1, height()/2-1), 2, width()+1)] = Stone::White;
  board_[std::slice(get_access_num(width()/2  , height()/2-1), 2, width()-1)] = Stone::Black;
}

bool GameBoard::can_continue() const
{
  for (auto target : board_) if (target == BoardBase::Stone::Space) return true;
  return false;
}
