#ifndef PLAYER_SERIES_H_
#define PLAYER_SERIES_H_

#include "GameBoard.hpp"
#include "OthelloAI.hpp"

class Player {
public:
  Player();
  const Player& operator=(const Player& src) = delete;
  virtual ~Player() = default;
  virtual void set_hand(const BoardSeries::GameBoard& game_board) = 0;
  BoardSeries::Position get_hand() const;
  void set_myname(std::string src);
  std::string get_myname() const;
protected:
  BoardSeries::Position hand_;
private:
  std::string myname_;
};

class HumanPlayer : public Player {
public:
  HumanPlayer();
  ~HumanPlayer() = default;
  void set_hand(const BoardSeries::GameBoard& game_board);
};

class ComputerPlayer : public Player{
public:
  ComputerPlayer(unsigned short seek_depth = 3);
  ~ComputerPlayer() = default;
  void set_hand(const BoardSeries::GameBoard& game_board);
private:
  unsigned short seek_depth_;
};

#endif // PLAYER_SERIES_H_
