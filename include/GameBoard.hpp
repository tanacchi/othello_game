#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_

#include <stdexcept>
#include <iostream>

#include "BoardBase.hpp"

namespace BoardSeries
{
class GameBoard : public BoardBase {
public:
  GameBoard(const Position size = Position{8, 8});
  const GameBoard& operator=(const GameBoard& src) = delete;
  void show() const;
  void init();
  bool can_continue() const;
  void put_dots();
  void remove_dots();
  char to_char(Stone stone) const;
};
};

#endif // GAME_BOARD_H_
