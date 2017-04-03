#include "BoardMaster.h"

class StoneScoreList {
  int hand_x;
  int hand_y;
  std::vector<int> score;
  int total_score;
public:
  StoneScoreList(int x, int y);
  void set_total_score();
  void get_coordinate(int &x, int &y);
  void set_score(int s);
  int get_total_score();
  void show_score_list();
};

class OthelloAI : private BoardMaster {
  int dist_x, dist_y;
  std::mt19937 rand_pos;
  std::vector<StoneScoreList> score_list;
public:
  OthelloAI();
  void get_current_board(BoardMaster game_board);
  void seek_effective_hand();
  void get_conclusion(int &x, int &y);
  void random_maker();
};
