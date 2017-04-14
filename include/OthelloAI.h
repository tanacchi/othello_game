#include "BoardMaster.h"

/*

1. 上の階層から階層番号とボード情報を受け取る
2. 下の階層へ階層番号とボード情報を流す
3. 上限階層orゲーム終了状態になるまで繰り返す

AIは1階層分だけ調べるようにして
新たにAIを統括するオブジェクトを作成

*/

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

class OthelloAI : private BoardMaster {
  int dist_x, dist_y;
  std::mt19937 rand_pos;
  std::vector<StoneScoreList> score_list;
public:
  OthelloAI(BoardMaster game_board, Stone mystone);
  ~OthelloAI();
  void get_conclusion(int &x, int &y);
  void random_maker();
  void seek();
  void record_dot_stone();
};
