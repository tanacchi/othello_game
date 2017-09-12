#ifndef OTHELLO_AI_H_
#define OTHELLO_AI_H_

#include "AiBoard.hpp"
#include "GameBoard.hpp"
#include <memory>

class ScoreList {
public:
  ScoreList(BoardSeries::Position pos);
  BoardSeries::Position get_position() const;
  void add_score(double score);
  void show_score_list() const;
  bool operator>(const ScoreList &right)const;
  double get_score() const;
private:
  BoardSeries::Position pos_;
  double score_;
};

class OthelloAI {
public:
  OthelloAI(const BoardSeries::GameBoard& game_board, unsigned short max_depth = 5);
  OthelloAI(const OthelloAI& src);
  const OthelloAI& operator=(const OthelloAI& src) = delete;
  ~OthelloAI();
  void set_score_list();
  BoardSeries::Position get_conclusion();
  double get_sub_score();
private:
  BoardSeries::AiBoard myboard_;
  unsigned short branch_;
  std::vector<ScoreList> score_list_;
  const unsigned short max_depth_;
  unsigned short mydepth_;
  OthelloAI* sub_;
};

#endif // OTHELLO_AI_H_