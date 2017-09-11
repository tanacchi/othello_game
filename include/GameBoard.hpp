#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_

#include <stdexcept>

#include "BoardBase.hpp"

namespace BoardSeries
{
class GameBoard : public BoardBase {
public:
  GameBoard(const Position size = Position{8, 8});
  const GameBoard& operator=(const GameBoard& src) = delete;
  void init();
  Stone get_active_stone() const;
  bool can_continue() const;
  void put_dots();
  void remove_dots();
};
};

#endif // GAME_BOARD_H_
