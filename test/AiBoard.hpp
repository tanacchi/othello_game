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
{ // とりあえず既存のやつ。gsliceがめっちゃ使えそう
  double status_score {0};
  Stone enemy_stone {get_enemy()};
  status_score = count_stone(active_stone_) - count_stone(enemy_stone);
  const std::vector<int> edge_x = {0, 0, 7, 7};   // REFACT : 絶対まとめた方がいい
  const std::vector<int> edge_y = {0, 7, 0, 7};
  for (int i = 0; i < 4; i++) {
    Stone target = board_[edge_y[i]][edge_x[i]];
    if (target == active_stone_) status_score += 15;
    else if (target == enemy_stone) status_score -= 15;
  }
  const std::vector<int> adv_x = {0, 0, 2, 2, 5, 5, 7, 7};
  const std::vector<int> adv_y = {2, 5, 0, 7, 0, 7, 2, 5};
  for (int i = 0; i < 8; i++) {
    Stone target = board_[adv_y[i]][adv_x[i]];
    if (target == active_stone_) status_score += 5;
    else if (target == enemy_stone) status_score -= 5;
  }
  const std::vector<int> pin_x = {0, 0, 1, 1, 1, 1, 6, 6, 6, 6, 7, 7};
  const std::vector<int> pin_y = {1, 6, 0, 1, 6, 7, 0, 1, 6, 7, 1, 6};
  for (int i = 0; i < 12; i++) {
    Stone target = board_[pin_y[i]][pin_x[i]];
    if (target == active_stone_) status_score -= 5;
    else if (target == enemy_stone) status_score += 5;
  }
  return status_score;
}

#endif // AI_BOARD_H_
