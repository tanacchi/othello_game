#ifndef PLAYER_SERIES_H_
#define PLAYER_SERIES_H_

#include "GameBoard.hpp"
#include "OthelloAI.hpp"

class Player {
public:
  Player();
  const Player& operator=(const Player& src) = delete;
  virtual ~Player() = default;
  virtual bool set_hand(const BoardSeries::GameBoard& game_board) = 0;
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
  bool set_hand(const BoardSeries::GameBoard& game_board);
};

class ComputerPlayer : public Player{
public:
  ComputerPlayer();
  ~ComputerPlayer() = default;
  bool set_hand(const BoardSeries::GameBoard& game_board);
};

#endif // PLAYER_SERIES_H_