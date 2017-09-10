#include "../include/OthelloAI.hpp"

ScoreList::ScoreList(BoardSeries::Position pos)
  : pos_  {pos},
    score_{0.0}
{
}

void ScoreList::get_position() const
{
  return pos_;
}

void ScoreList::add_score(double score)
{
  score_ += score;
}

void ScoreList::show_score_list() const
{
  std::cout << "x = " << static_cast<short>(pos_.x + 1) << ", "
            << "y = " << static_cast<short>(pos_.y + 1) << ' ';
  std::cout << "Score : " << score_ << std::endl;
}

bool ScoreList::operator>(const ScoreList &right ) const
{
  return total_score_ > right.total_score_;
}

int ScoreList::get_score() const
{
  return score_;
}

OthelloAI::OthelloAI(GameBoard game_board, unsigned short max_depth = 5)
  : myboard_    {game_board},
    branch_     {0},
    score_list_ {},
    max_depth_  {max_depth},
    mydepth_    {0},
    sub_      {0},
    dist_pos_   {-1, -1}
{
  set_score_list();
}

OthelloAI::OthelloAI(const OthelloAI& src)
  : myboard_    {src.myboard_},
    branch_     {0},
    score_list_ {},
    max_depth_  {src.max_depth_},
    mydepth_    {src.mydepth_},
    sub_      {0},
    dist_pos_   {-1, -1}
{
  set_score_list();
}

OthelloAI::~OthelloAI()
{
  if (mydepth_ > 0 && branch_ > 0) delete[] subAI_;
}

inline void OthelloAI::set_score_list()
{
  BoardSeries::Position target{0, 0};
  for (target.y = 0; target.y < myboard_.height(); ++target.y)
    for (target.x = 0; target.x < myboard_.width(); ++target.x)
      if (myboard_.is_available_position(target)) score_list_.push_back(ScoreList{target});
}

BoardSeries::Position OthelloAI::get_conclusion() const
{
}

double OthelloAI::get_sub_score()
{
}
