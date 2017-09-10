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
    subAI_      {0},
    dist_pos_   {-1, -1}
{
}

OthelloAI::OthelloAI(const OthelloAI& src)
  : myboard_    {src.myboard_},
    branch_     {0},
    score_list_ {},
    max_depth_  {src.max_depth_},
    mydepth_    {src.mydepth_},
    subAI_      {0},
    dist_pos_   {-1, -1}
{
}

OthelloAI::~OthelloAI()
{
  if (mydepth_ > 0 && branch_ > 0) delete[] subAI_;
}

void OthelloAI::set_subAI(int depth)
{
  mydepth_ = depth;
  record_dot_stone();
  branch_ = score_list_.size();
  if (mydepth_ < 1 || branch_ < 1) return;
  subAI_ = new OthelloAI[branch_];
  for (int i = 0; i < branch_; i++)  {
    subAI_[i] = *this;
    int x, y;
    score_list_[i].get_coordinate(x, y);
    score_list_[i].add_Score(virtual_board_.count_reversible_stone(x, y));
    subAI_[i].virtual_board_.insert(x, y);
    subAI_[i].virtual_board_.reverse_stone(x, y);
    score_list_[i].add_Score(virtual_board_.get_status_score());
    subAI_[i].virtual_board_.switch_active_stone();
    subAI_[i].set_subAI(mydepth_-1);      
  }
}

BoardSeries::Position OthelloAI::get_conclusion() const
{
}

void OthelloAI::seek(int max_depth)
{
  set_subAI(max_depth);
  for (size_t i = 0; i < score_list_.size(); i++) {
    int x, y;
    score_list_[i].get_coordinate(x, y);
    score_list_[i].add_Score(virtual_board_.count_reversible_stone(x, y));
    score_list_[i].add_Score(virtual_board_.get_status_score());
    score_list_[i].add_Score(subAI_[i].get_avarage_score());
    score_list_[i].set_total_score();
  }
  std::sort(score_list_.begin(), score_list_.end(), std::greater<ScoreList>()); // REFACT : 要は最大値を取る奴の中でランダム参照したい
  for (size_t i = 0; i < score_list_.size(); i++) score_list_[i].show_score_list();
  // double best_score = score_list_[0].get_score();
  // std::vector<ScoreList>::iterator p = score_list_.begin();
  // while (p->get_score() == best_score) p++;
  // score_list_.erase(p, score_list_.end());
  // std::cout << "Hey" << std::endl;
  // for (size_t i = 0; i < score_list_.size(); i++) score_list_[i].show_score_list_();
  // std::shuffle(score_list_.begin(), score_list_.end(), rand_pos);
  score_list_[0].get_coordinate(dist_x_, dist_y_);
}

inline void OthelloAI::set_score_list()
{
  BoardSeries::Position target{0, 0};
  for (target.y = 0; target.y < myboard_.height(); ++target.y)
    for (target.x = 0; target.x < myboard_.width(); ++target.x)
      if (myboard_.is_available_position(target)) score_list_.push_back(ScoreList{target});
}

double OthelloAI::get_avarage_score()
{
  if (mydepth_ < 1 || branch_ < 1) { 
    return virtual_board_.get_status_score();
  }
  double sum = 0;
  for (int i = 0; i < branch_; i++) {
    // score_list_[i].set_total_score();
    // sum += score_list_[i].get_score();
    sum += subAI_[i].get_avarage_score();
  }
  return sum / (double)branch_;    
}
