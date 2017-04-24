#include "include/OthelloAI.h"

#define EDGE_SCORE 10.5

int global;

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

void StoneScoreList::set_score(int s) {
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

OthelloAI::OthelloAI(BoardMaster game_board)
  : rand_pos {std::random_device{}()},
    virtual_board{game_board},
    serial_num{global++}
{
}

OthelloAI::OthelloAI()
  : mydepth{0},
    serial_num{global++}
{
}

OthelloAI::~OthelloAI()
{
  if (mydepth > 0) delete[] subAI;
}

OthelloAI& OthelloAI::operator=(OthelloAI& src) {
  virtual_board = src.virtual_board;
  return *this;
}

void OthelloAI::set_subAI(int depth) {
  mydepth = depth;
  record_dot_stone();
  if (mydepth > 0) {
    branch = score_list.size();
    subAI = new OthelloAI[branch];
    for (int i = 0; i < branch; i++)  {
      subAI[i] = *this;
      int x, y;
      score_list[i].get_coordinate(x, y);
      subAI[i].virtual_board.insert(x, y);
      subAI[i].virtual_board.reverse_stone(x, y);
      std::cout << "mydepth = " << mydepth << '\n'
                << i+1 << '/' << branch << std::endl;
      subAI[i].virtual_board.show();
      subAI[i].virtual_board.switch_active_stone();
      subAI[i].set_subAI(depth-1);      
    }
  }
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

void OthelloAI::seek(int max_depth) {
  set_subAI(max_depth);
  for (int i = 0; i < score_list.size(); i++) {
    int x, y;
    score_list[i].get_coordinate(x, y);
    score_list[i].set_score(subAI[i].get_avarage_score());
    score_list[i].set_total_score();
  }
  std::sort(score_list.begin(), score_list.end(), std::greater<StoneScoreList>());
  for (int i = 0; i < score_list.size(); i++) score_list[i].show_score_list();
  // std::cout << "HELLO!!\n";
  // std::shuffle(score_list.begin(), score_list.end(), rand_pos);
  // for (int i = 0; i < score_list.size(); i++) score_list[i].show_score_list();
  score_list[0].get_coordinate(dist_x, dist_y);
}

void OthelloAI::record_dot_stone() {
  for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
      if (virtual_board.is_available_position(j, i)) score_list.push_back(StoneScoreList(j, i));
}

double OthelloAI::get_avarage_score() {
  if (mydepth > 0) {
    double sum;
    for (int i = 0; i < branch; i++) sum += subAI[i].get_avarage_score();
    return sum / (double)branch;
  }
  else return virtual_board.get_status_score();
}
