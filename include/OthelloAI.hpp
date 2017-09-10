#ifndef OTHELLO_AI_H_
#define OTHELLO_AI_H_

#include "AiBoard.hpp"
#include <memory>

class ScoreList {
 public:
  ScoreList(int x, int y);
  ~ScoreList() = default;
  void set_total_score();
  void get_coordinate(int &x, int &y) const;
  void set_score(double s);
  void set_score(int s);
  void show_score_list() const;
  bool operator>(const ScoreList &right)const;
  int get_total_score() const;
 private:
  int hand_x_;
  int hand_y_;
  std::vector<double> score_;
  double total_score_;
};

class OthelloAI {
 public:
  OthelloAI();
  OthelloAI(BoardMaster game_board);
  OthelloAI& operator=(OthelloAI& src);
  ~OthelloAI();
  void get_conclusion(int &x, int &y) const;
  void random_maker();
  void seek(int max_depth);
  void record_dot_stone();
  void set_subAI(int branch);
  double get_avarage_score();
 private:
  int dist_x_, dist_y_;
  std::mt19937 rand_pos_;
  std::vector<ScoreList> score_list_;
  BoardMaster virtual_board_;
  int mydepth_;
  OthelloAI* subAI_;
  int serial_num_;
  int branch_;
};

#endif // OTHELLO_AI_H_
