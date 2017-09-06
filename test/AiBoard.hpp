#ifndef AI_BOARD_H_
#define AI_BOARD_H_

#include "BoardBase.hpp"


class AiBoard : public BoardBase {
public:
  AiBoard(const BoardBase& src);
  const AiBoard& operator=(const AiBoard& src) = delete;
  double get_status_score() const;
};

AiBoard::AiBoard(const BoardBase& src)
  : BoardBase(src)
{
}

double AiBoard::get_status_score() const
{ // とりあえず既存のやつ。gsliceもalgorithmもめっちゃ使えそう
  double status_score {0};
  const Stone enemy_stone {get_enemy_stone()};
  BoardBase::Stone target{BoardBase::Stone::Space};
  const std::vector<Position> edge_pos = {
    {0, 0}, {7, 0},
    {0, 7}, {7, 7}
  };
  for (int i = 0; i < 4; i++) {
    target = board_[get_access_num(edge_pos[i])];
    if (target == active_stone_) status_score += 15;
    else if (target == enemy_stone) status_score -= 15;
  }
  const std::vector<Position> near_pos = {
            {1, 0}, {6, 0},
    {0, 1}, {1, 1}, {6, 1}, {7, 1},
    {0, 6}, {1, 6}, {6, 6}, {7, 6},
            {1, 7}, {6, 7}
  };
  for (int i = 0; i < 12; i++) {
    target = board_[get_access_num(near_pos[i])];
    if (target == active_stone_) status_score -= 5;
    else if (target == enemy_stone) status_score += 5;
  }
  const std::vector<Position> reach_pos = {
                    {2, 0}, {5, 0},
                    {2, 1}, {5, 1},
    {0, 2}, {1, 2}, {2, 2}, {5, 2}, {6, 2}, {7, 2},
    {0, 5}, {1, 5}, {2, 5}, {5, 5}, {6, 5}, {7, 5},
                    {2, 6}, {5, 6},
                    {2, 7}, {5, 7}
  };
  for (int i = 0; i < 8; i++) {
    target = board_[get_access_num(reach_pos[i])];
    if (target == active_stone_) status_score += 5;
    else if (target == enemy_stone) status_score -= 5;
  }
  return status_score;
}

#endif // AI_BOARD_H_
