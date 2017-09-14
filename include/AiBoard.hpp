#ifndef AI_BOARD_H_
#define AI_BOARD_H_

#include "BoardBase.hpp"

namespace BoardSeries
{
static const std::vector<Position> edge_pos = {
  {0, 0}, {7, 0},
  {0, 7}, {7, 7}
};

static const std::vector<Position> near_pos = {
          {1, 0}, {6, 0},
  {0, 1}, {1, 1}, {6, 1}, {7, 1},
  {0, 6}, {1, 6}, {6, 6}, {7, 6},
          {1, 7}, {6, 7}
};

static const std::vector<Position> reach_pos = {
                  {2, 0}, {5, 0},
                  {2, 1}, {5, 1},
  {0, 2}, {1, 2}, {2, 2}, {5, 2}, {6, 2}, {7, 2},
  {0, 5}, {1, 5}, {2, 5}, {5, 5}, {6, 5}, {7, 5},
                  {2, 6}, {5, 6},
                  {2, 7}, {5, 7}
};

class AiBoard : public BoardBase {
public:
  AiBoard(BoardBase src);
  const AiBoard& operator=(const AiBoard& src) = delete;
  float get_status_score() const;
};
};

#endif // AI_BOARD_H_
