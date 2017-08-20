#ifndef OTHELLO_AI_H_
#define OTHELLO_AI_H_

#include "BoardMaster.hpp"
#include <memory>

class StoneScoreList {
 public:
  StoneScoreList(int x, int y);
  ~StoneScoreList() = default;
  void set_total_score();
  void get_coordinate(int &x, int &y);
  void set_score(double s);
  void set_score(int s);
  void show_score_list();
  bool operator>(const StoneScoreList &right)const;
  int get_total_score();
 private:
  int hand_x_;
  int hand_y_;
  std::vector<double> score_;
  double total_score_;
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
  int dist_x_, dist_y_;
  std::mt19937 rand_pos_;
  std::vector<StoneScoreList> score_list_;
  BoardMaster virtual_board_;
  int mydepth_;
  OthelloAI* subAI_;
  int serial_num_;
  int branch_;
};

#endif // OTHELLO_AI_H_
