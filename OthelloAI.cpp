#include "include/OthelloAI.h"

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
  score.push_back(s);
}
int StoneScoreList::get_total_score() {
  return total_score;
}
void StoneScoreList::show_score_list() {
  std::cout << "x = " << hand_x+1 << ", y = " << hand_y+1 << ' ';
  std::cout << "Score : " << total_score << std::endl;
}

bool StoneScoreList::operator>(const StoneScoreList &right ) const {
  return total_score > right.total_score;
}

// ------------------------- OthelloAI -----------------------------------------

OthelloAI::OthelloAI(BoardMaster game_board, Stone active_stone) : rand_pos { std::random_device{}() } {
  for (size_t i {0}; i < BOARD_SIZE; i++)
    for (size_t j {0}; j < BOARD_SIZE; j++)
      insert_stone(j, i, game_board.get_stone(j, i));
  set_active_stone(active_stone);
}

OthelloAI::~OthelloAI() {
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

void OthelloAI::seek_effective_hand() {
  put_dot_stone();
  for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
      if (stone_compare(j, i, Stone::DOT)) score_list.push_back(StoneScoreList(j, i));
  int x, y;
  for (int i = 0; i < score_list.size(); i++) {
    score_list[i].get_coordinate(x, y);
    if (is_edge(x, y)) score_list[i].set_score(10);
    score_list[i].set_score(count_reversible_stone(x, y));
    score_list[i].set_total_score();
  }
  std::sort(score_list.begin(), score_list.end(), std::greater<StoneScoreList>());  
  for (int i = 0; i < score_list.size(); i++) score_list[i].show_score_list();
  score_list[0].get_coordinate(x, y);
  dist_x = x; dist_y = y;
}

bool OthelloAI::is_edge(int x, int y) {
  return (x == 0 && (y == 0 || y == 7)) || (x == 7 && (y == 0 || y == 7));
}
