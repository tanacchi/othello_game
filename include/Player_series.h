#include "OthelloAI.h"

class Player {
  Stone my_stone;
protected:
  int hand_x, hand_y;
public:
  void set_my_stone(Stone stone);
  virtual void set_hand(BoardMaster game_board);
  Stone get_my_stone();
  void get_hand(int &x, int &y);
};

class HumanPlayer : public Player {
public:
  void set_hand(BoardMaster game_board);
};

class ComputerPlayer : public Player{
public:
  void set_hand(BoardMaster game_board);
};
