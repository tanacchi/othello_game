#include "BoardMaster.h"

class StoneScoreList {
  int hand_x;
  int hand_y;
  std::vector<double> score;
  double total_score;
public:
  StoneScoreList(int x, int y);
  void set_total_score();
  void get_coordinate(int &x, int &y);
  void set_score(double s);
  void show_score_list();
  bool operator>(const StoneScoreList &right)const;
  inline bool is_edge(int x, int y);
};

class OthelloAI {
  int dist_x, dist_y;
  std::mt19937 rand_pos;
  std::vector<StoneScoreList> score_list;
  BoardMaster virtual_board;
  int mydepth;
  OthelloAI* subAI;
  int serial_num;
 public:
  OthelloAI(BoardMaster game_board, int max_depth);
  OthelloAI();
  ~OthelloAI();
  OthelloAI& operator=(OthelloAI& src);
  void get_conclusion(int &x, int &y);
  void random_maker();
  void seek();
  void record_dot_stone();
  void set_subAI(int branch);
  void get_board(BoardMaster &myboard);
  int get_mydepth();
};
