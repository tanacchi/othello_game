#include "OthelloAI.h"

class Player {
  Stone mystone;
protected:
  int hand_x, hand_y;
public:
  void set_mystone(Stone stone);
  virtual void set_hand(const BoardMaster game_board) = 0;
  Stone get_mystone();
  void get_hand(int &x, int &y);
};

class HumanPlayer : public Player {
public:
  void set_hand(const BoardMaster game_board);
};

class ComputerPlayer : public Player{
public:
  void set_hand(const BoardMaster game_board);
};
