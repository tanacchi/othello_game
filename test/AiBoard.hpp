#ifndef AI_BOARD_H_
#define AI_BOARD_H_

#include "BoardBase.hpp"

class AiBoard : public BoardBase {
public:
  AiBoard();
  const AiBoard& operator=(const AiBoard& src) = delete;
  double get_status_score() const;
};

double AiBoard::get_status_score() const
{
  double status_score {0};
  return status_score;
}

#endif // AI_BOARD_H_
