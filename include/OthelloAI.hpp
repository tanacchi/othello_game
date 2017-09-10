#ifndef OTHELLO_AI_H_
#define OTHELLO_AI_H_

#include "AiBoard.hpp"
#include <memory>

class ScoreList {
 public:
  ScoreList(BoardSeries::Position pos);
  ~ScoreList() = default;
  void get_position() const;
  void add_score(double score);
  void show_score_list() const;
  bool operator>(const ScoreList &right)const;
  int get_score() const;
 private:
  BoardSeries::Position pos_;
  double score_;
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
  BoardSeries::Position dist_pos_;
  std::mt19937 rand_pos_;
  std::vector<ScoreList> score_list_;
  AiBoard virtual_board_;
  int mydepth_;
  OthelloAI* subAI_;
  int serial_num_;
  int branch_;
};

#endif // OTHELLO_AI_H_
