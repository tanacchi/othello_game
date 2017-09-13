#ifndef AI_BOARD_H_
#define AI_BOARD_H_

#include "BoardBase.hpp"

namespace BoardSeries
{
class AiBoard : public BoardBase {
public:
  AiBoard(BoardBase src);
  const AiBoard& operator=(const AiBoard& src) = delete;
  float get_status_score() const;
};
};

#endif // AI_BOARD_H_
