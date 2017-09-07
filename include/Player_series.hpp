#ifndef PLAYER_SERIES_H_
#define PLAYER_SERIES_H_

#include "GameBoard.hpp"
#include "OthelloAI.hpp"

class Player {
public:
  Player();
  virtual ~Player() = default;
  // void set_mystone(Stone stone);
  virtual bool set_hand(const BoardMaster game_board) = 0;
  // Stone get_mystone() const;
  BoardBase::Position get_hand() const;
  void set_myname(std::string src);
  std::string get_myname() const;
protected:
  BoardBase::Position hand_;
private:
  Player(const Player& src);
  const Player& operator=(const Player& src);
  // Stone mystone_;
  std::string myname_;
};

class HumanPlayer : public Player {
public:
  HumanPlayer();
  ~HumanPlayer() = default;
  bool set_hand(const GameBoard& game_board);
};

class ComputerPlayer : public Player{
public:
  ComputerPlayer();
  ~ComputerPlayer() = default;
  bool set_hand(const GameBoard& game_board);
};

#endif // PLAYER_SERIES_H_
