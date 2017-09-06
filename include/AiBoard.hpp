#ifndef AI_BOARD_H_
#define AI_BOARD_H_

#include "BoardBase.hpp"

class AiBoard : public BoardBase {
public:
  AiBoard(const BoardBase& src);
  const AiBoard& operator=(const AiBoard& src) = delete;
  double get_status_score() const;
};

#endif // AI_BOARD_H_
