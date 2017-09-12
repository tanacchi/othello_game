#include "../include/AiBoard.hpp"

namespace BoardSeries
{
AiBoard::AiBoard(BoardBase src)
  : BoardBase(src)
{
}

double AiBoard::get_status_score() const
{ // とりあえず既存のやつ。gsliceもalgorithmもめっちゃ使えそう
  const Stone enemy_stone {get_enemy_stone()};
  double status_score {static_cast<double>(count_stone(active_stone_) - count_stone(enemy_stone))};
  Stone target{Stone::Space};
  static const std::vector<Position> edge_pos = {
    {0,          0}, {width()-1,          0},
    {0, height()-1}, {width()-1, height()-1}
  };
  for (int i{0}; i < 4; ++i) {
    target = board_[get_access_num(edge_pos[i])];
    if (target == active_stone_) status_score += 15;
    else if (target == enemy_stone) status_score += -15;
  }
  static const std::vector<Position> near_pos = {
                     {1,          0}, {width()-2,          0},
    {0,          1}, {1,          1}, {width()-2,          1}, {width()-1,          1},
    {0, height()-2}, {1, height()-2}, {width()-2, height()-2}, {width()-1, height()-2},
                     {1, height()-1}, {width()-2, height()-1}
  };
  for (int i{0}; i < 12; ++i) {
    target = board_[get_access_num(near_pos[i])];
    if (target == active_stone_) status_score += -5;
    else if (target == enemy_stone) status_score += 5;
  }
  static const std::vector<Position> reach_pos = {
                                      {2,          0}, {width()-3,          0},
                                      {2,          1}, {width()-3,          1},
    {0,          2}, {1,          2}, {2,          2}, {width()-3,          2}, {width()-2,          2}, {width()-1,          2},
    {0, height()-3}, {1, height()-3}, {2, height()-3}, {width()-3, height()-3}, {width()-2, height()-3}, {width()-1, height()-3},
                                      {2, height()-2}, {width()-3, height()-2},
                                      {2, height()-1}, {width()-3, height()-1}
  };
  for (int i{0}; i < 8; ++i) {
    target = board_[get_access_num(reach_pos[i])];
    if (target == active_stone_) status_score += 5;
    else if (target == enemy_stone) status_score += -5;
  }
  return status_score;
}
};
