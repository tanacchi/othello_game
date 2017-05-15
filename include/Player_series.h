#include "OthelloAI.h"

class Player {
  Stone mystone;
  std::string myname;
  std::vector<StoneScoreList> score_list;
protected:
  int hand_x, hand_y;
public:
  void set_mystone(Stone stone);
  virtual bool set_hand(const BoardMaster game_board) = 0;
  Stone get_mystone();
  void get_hand(int &x, int &y);
  void set_myname(std::string src);
  std::string get_myname();
};

class HumanPlayer : public Player {
public:
  HumanPlayer();
  bool set_hand(const BoardMaster game_board);
};

class ComputerPlayer : public Player{
public:
  ComputerPlayer();
  bool set_hand(const BoardMaster game_board);
};
