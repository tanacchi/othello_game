#include "../include/AiBoard.hpp"

namespace BoardSeries
{
AiBoard::AiBoard(BoardBase src)
  : BoardBase(src)
{
}

float AiBoard::get_status_score() const
{ // とりあえず既存のやつ。gsliceもalgorithmもめっちゃ使えそう
  const Stone enemy_stone {get_enemy_stone()};
  float status_score {static_cast<float>(count_stone(active_stone_) - count_stone(enemy_stone))};
  Stone target{Stone::Space};
  for (const auto& edge : edge_pos) {
    target = board_[get_access_num(edge)];
    if (target == active_stone_) status_score += 15;
    else if (target == enemy_stone) status_score += -15;
  }
  for (const auto& near : near_pos) {
    target = board_[get_access_num(near)];
    if (target == active_stone_) status_score += -5;
    else if (target == enemy_stone) status_score += 5;
  }
  for (const auto& reach : reach_pos) {
    target = board_[get_access_num(reach)];
    if (target == active_stone_) status_score += 5;
    else if (target == enemy_stone) status_score += -5;
  }
  return status_score;
}
};
