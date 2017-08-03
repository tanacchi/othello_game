#include "BoardMaster.h"

class StoneScoreList {
 public:
  StoneScoreList(int x, int y);
  void set_total_score();
  void get_coordinate(int &x, int &y);
  void set_score(double s);
  void set_score(int s);
  void show_score_list();
  bool operator>(const StoneScoreList &right)const;
  int get_total_score();
 private:
  int hand_x;
  int hand_y;
  std::vector<double> score;
  double total_score;
};

class OthelloAI {
 public:
  OthelloAI(BoardMaster game_board);
  OthelloAI();
  ~OthelloAI();
  OthelloAI& operator=(OthelloAI& src);
  void get_conclusion(int &x, int &y);
  void random_maker();
  void seek(int max_depth);
  void record_dot_stone();
  void set_subAI(int branch);
  double get_avarage_score();
 private:
  int dist_x, dist_y;
  std::mt19937 rand_pos;
  std::vector<StoneScoreList> score_list;
  BoardMaster virtual_board;
  int mydepth;
  OthelloAI* subAI;
  int serial_num;
  int branch;
};
