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
{
  double status_score {0};
  std::valarray<std::size_t> edge_pos = {
    0,                             get_access_num(width()-1, 0),
    get_access_num(0, height()-1), width()*height()-1
  };
  std::valarray<BoardBase::Stone> edge{board_[edge_pos]};
  return status_score;
}

#endif // AI_BOARD_H_
