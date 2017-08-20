#ifndef PLAYER_SERIES_H_
#define PLAYER_SERIES_H_

#include "OthelloAI.hpp"

class Player {
public:
  Player();
  virtual ~Player() = default;
  void set_mystone(Stone stone);
  virtual bool set_hand(const BoardMaster game_board) = 0;
  Stone get_mystone();
  void get_hand(int &x, int &y);
  void set_myname(std::string src);
  std::string get_myname();
private:
  Stone mystone_;
  std::string myname_;
protected:
  int hand_x_, hand_y_;
};

class HumanPlayer : public Player {
public:
  HumanPlayer();
  ~HumanPlayer() = default;
  bool set_hand(const BoardMaster game_board);
};

class ComputerPlayer : public Player{
public:
  ComputerPlayer();
  ~ComputerPlayer() = default;
  bool set_hand(const BoardMaster game_board);
};

#endif // PLAYER_SERIES_H_
