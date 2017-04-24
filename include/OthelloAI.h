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
  int branch;
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
  long long get_avarage_score();
};
