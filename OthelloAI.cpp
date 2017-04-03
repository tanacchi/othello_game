#include "include/OthelloAI.h"

StoneScoreList::StoneScoreList(int x, int y) {
  hand_x = x; hand_y = y;
}
 
void StoneScoreList::set_total_score() {
  for (int i = 0; i < score.size(); i++) total_score += score[i];
}

void StoneScoreList::get_coordinate(int &x, int &y) {
  x = hand_x; y = hand_y;
}
void StoneScoreList::set_score(int s) {
  // score.push_back(s);
  total_score = s;
}
int StoneScoreList::get_total_score() {
  return total_score;
}
void StoneScoreList::show_score_list() {
  std::cout << "x = " << hand_x << ", y = " << hand_y << ' ';
  std::cout << "Score : " << total_score << std::endl;
}



void OthelloAI::get_current_board(BoardMaster game_board) {
  for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
      insert_stone(j, i, game_board.get_stone(j, i));
}

void OthelloAI::get_conclusion(int &x, int &y) { 
  x = dist_x;
  y = dist_y;
}

OthelloAI::OthelloAI() : rand_pos { std::random_device{}() }
{
}

void OthelloAI::random_maker() {
  std::uniform_int_distribution<int> rand100(0, 7);
  dist_x = rand100(rand_pos);
  dist_y = rand100(rand_pos);
}

void OthelloAI::seek_effective_hand() {  // !!!!!!!!!!!!!!!!!!!!!
}
