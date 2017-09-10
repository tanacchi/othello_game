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
  return score_ > right.score_;
}

double ScoreList::get_score() const
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
  get_sub_score();
  std::sort(score_list_.begin(), score_list_.end(), std::greater<ScoreList>());
  return score_list_[0].get_position();
}

double OthelloAI::get_sub_score()
{
  if ((max_depth_ - mydepth) < 0 || score_list_.empty())
    return myboard_.get_status_score();
  for (int i{0}; i < score_list.size(); ++i) {
    sub_ = new OthelloAI(*this);
    sub_->mydepth++;
    sub_->myboard_.insert(score_list_[i].get_position());
    sub_->myboard_.switch_active_stone();
    score_list_[i].add_score(sub_->get_sub_score());
    delete sub_;
  }
  double sum{0};
  for (int i{0}; i < score_list_.size(); ++i) sum += score_list_[i].get_score();
  return sum / score_list_.size();
}
