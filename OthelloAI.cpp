#include "include/OthelloAI.h"

#define EDGE_SCORE 10

// ------------------------- StoneList -----------------------------------------

StoneScoreList::StoneScoreList(int x, int y) {
  hand_x = x; hand_y = y; total_score = 0;
}
 
void StoneScoreList::set_total_score() {
  for (size_t i {0}; i < score.size(); i++) total_score += score[i];
}

void StoneScoreList::get_coordinate(int &x, int &y) {
  x = hand_x; y = hand_y;
}

void StoneScoreList::set_score(double s) {
  if (is_edge(hand_x, hand_y)) s += EDGE_SCORE;
  score.push_back(s);
}

void StoneScoreList::show_score_list() {
  std::cout << "x = " << hand_x+1 << ", y = " << hand_y+1 << ' ';
  std::cout << "Score : " << total_score << std::endl;
}

bool StoneScoreList::operator>(const StoneScoreList &right ) const {
  return total_score > right.total_score;
}

inline bool StoneScoreList::is_edge(int x, int y) {
  return (!x || x == 7) && (!y || y == 7);
}

// ------------------------- OthelloAI -----------------------------------------

OthelloAI::OthelloAI(BoardMaster game_board, int max_depth)
  : rand_pos {std::random_device{}()},
    virtual_board{game_board},
    current_depth{max_depth}
{ 
}

OthelloAI::OthelloAI()
  : current_depth{0}
{
}

OthelloAI::~OthelloAI()
{
}

OthelloAI OthelloAI::operator=(OthelloAI src) {
  virtual_board = src.virtual_board;                     // XXX : なんかすごいエラー吐かれる
  current_depth = src.current_depth;
  return *this;
}

void OthelloAI::set_subAI(int branch) {
  subAI = new OthelloAI[branch];
  for (int i = 0; i < branch; i++) subAI[i] = *this;
}

void OthelloAI::random_maker() {
  std::uniform_int_distribution<int> rand100(0, 7);
  dist_x = rand100(rand_pos);
  dist_y = rand100(rand_pos);
}

void OthelloAI::get_conclusion(int &x, int &y) {
  x = dist_x;
  y = dist_y;
}

void OthelloAI::seek() {
  record_dot_stone();
  for (int i = 0; i < score_list.size(); i++) {
    int x, y;
    score_list[i].get_coordinate(x, y);
    score_list[i].set_score(virtual_board.count_reversible_stone(x, y));
    //    set_subAI(virtual_board.count_reversible_stone(x, y));
    score_list[i].set_total_score();
  }
  std::sort(score_list.begin(), score_list.end(), std::greater<StoneScoreList>());
  for (int i = 0; i < score_list.size(); i++) score_list[i].show_score_list();
  std::cout << "HELLO!!\n";
  std::shuffle(score_list.begin(), score_list.end(), rand_pos);
  for (int i = 0; i < score_list.size(); i++) score_list[i].show_score_list();
  score_list[0].get_coordinate(dist_x, dist_y);
}

void OthelloAI::record_dot_stone() {
  for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
      if (virtual_board.is_available_position(j, i)) score_list.push_back(StoneScoreList(j, i));
}

void OthelloAI::get_board(BoardMaster &myboard) {
  myboard = virtual_board;
}
