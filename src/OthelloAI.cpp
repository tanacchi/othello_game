#include <iterator>

#include "../include/OthelloAI.hpp"

ScoreList::ScoreList(BoardSeries::Position pos)
  : pos_  {pos},
    score_{0.0}
{
}

BoardSeries::Position ScoreList::get_position() const
{
  return pos_;
}

void ScoreList::add_score(float score)
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

float ScoreList::get_score() const
{
  return score_;
}

OthelloAI::OthelloAI(const BoardSeries::GameBoard& game_board, unsigned short max_depth)
  : myboard_    {game_board},
    branch_     {0},
    score_list_ {},
    max_depth_  {max_depth},
    mydepth_    {0},
    sub_        {nullptr}
{
  set_score_list();
}

OthelloAI::OthelloAI(const OthelloAI& src)
  : myboard_    {src.myboard_},
    branch_     {0},
    score_list_ {},
    max_depth_  {src.max_depth_},
    mydepth_    {src.mydepth_},
    sub_        {nullptr}
{
  set_score_list();
}

inline void OthelloAI::set_score_list()
{
  BoardSeries::Position target{0, 0};
  for (target.y = 0; target.y < myboard_.height(); ++target.y)
    for (target.x = 0; target.x < myboard_.width(); ++target.x)
      if (myboard_.is_available_position(target)) score_list_.push_back(ScoreList{target});
}

BoardSeries::Position OthelloAI::get_conclusion()
{
  get_sub_score();
  std::sort(score_list_.begin(), score_list_.end(), std::greater<ScoreList>());
  for (auto sl : score_list_) sl.show_score_list();
  return score_list_[0].get_position();
}

float OthelloAI::get_sub_score()
{
  if ((max_depth_ - mydepth_) < 0 || score_list_.empty()) {
    if ((mydepth_ % 2) != 0) myboard_.switch_active_stone();
    return myboard_.get_status_score();
  }
  for (std::size_t i{0}; i < score_list_.size(); ++i) {
    sub_ = new OthelloAI(*this);
    sub_->mydepth_++;
    sub_->myboard_.insert(score_list_[i].get_position());
    sub_->myboard_.switch_active_stone();
    // show(myboard_);
    score_list_[i].add_score(sub_->get_sub_score());
    delete sub_;
  }
  float sum{myboard_.get_status_score()};
  for (std::size_t i{0}; i < score_list_.size(); ++i) sum += score_list_[i].get_score();
  return (sum * (mydepth_ + 1)) / score_list_.size() / 10;
}
