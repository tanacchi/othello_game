#ifndef NEW_GAME_MASTER_H_
#define NEW_GAME_MASTER_H_

#include <fstream>

#include "GameBoard.hpp"
#include "AiBoard.hpp"
#include "PlayerSeries.hpp"

class HandList {
public:
  HandList(short turn, BoardSeries::Stone stone, BoardSeries::Position position);
  void rewrite(BoardSeries::GameBoard& game_board) const;
  void report(std::ofstream& log_file) const;
private:
  short turn_;
  BoardSeries::Stone stone_;
  BoardSeries::Position position_;
};

class GameMaster {
public:
  enum class Task {
    Init,
    Op,
    Set,
    Insert,
    Revert,
    Write,
    Judge,
    Switch,
    Ask,
    Ed
  };
  GameMaster(PlaneVector board_size, Player* player[]);
  ~GameMaster() = default;
  Task run(Task mode);
  Task task_init();
  Task task_op();
  Task task_set();
  Task task_insert();
  Task task_revert();
  Task task_write();
  Task task_judge();
  Task task_switch();
  Task task_ask();
  void record_hand_list();
private:
  BoardSeries::GameBoard board_;
  Player *participant_[2];
  Player *active_player_;
  short turn_;
  BoardSeries::Position pos_;
  std::vector<HandList> hand_list_;
  std::ofstream log_file_;
};

#endif // NEW_GAME_MASTER_H_
