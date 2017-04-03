#include "OthelloAI.h"

class Player {
  Stone my_stone;
  int hand_x, hand_y;
public:
  void set_my_stone(Stone stone);
  void input_position(const int input_x, const int input_y);
  virtual void set_hand();
  Stone get_my_stone();
  void get_hand(int &x, int &y);
};

class HumanPlayer : public Player {
public:
  void set_hand();
};

class ComputerPlayer : public Player, private OthelloAI {
public:
  void set_hand();
};