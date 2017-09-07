#ifndef PLAYER_SERIES_H_
#define PLAYER_SERIES_H_

#include "GameBoard.hpp"
#include "OthelloAI.hpp"

class Player {
public:
  Player(BoardBase::Stone mystone);
  const Player& operator=(const Player& src) = delete;
  virtual ~Player() = default;
  virtual bool set_hand(const BoardMaster game_board) = 0;
  BoardBase::Stone get_mystone() const;
  BoardBase::Position get_hand() const;
  void set_myname(std::string src);
  std::string get_myname() const;
protected:
  BoardBase::Position hand_;
private:
  BoardBase::Stone mystone_;
  std::string myname_;
};

class HumanPlayer : public Player {
public:
  HumanPlayer(BoardBase::Stone mystone = BoardBase::Stone::Space);
  ~HumanPlayer() = default;
  bool set_hand(const GameBoard& game_board);
};

class ComputerPlayer : public Player{
public:
  ComputerPlayer(BoardBase::Stone mystone = BoardBase::Stone::Space);
  ~ComputerPlayer() = default;
  bool set_hand(const GameBoard& game_board);
};

#endif // PLAYER_SERIES_H_
