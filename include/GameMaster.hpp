#ifndef GAME_MASTER_H_
#define GAME_MASTER_H_

#include "../include/Player_series.hpp"

enum class Task {
  INIT,
  OP,
  SET,
  INSERT,
  REVERT,
  WRITE,
  JUDGE,
  SWITCH,
  ASK,
  ED
};

enum class Mode {
  NORMAL_H,
  NORMAL_C,
  PERSONAL,
  AUTO,
  FALSE
};

class HandList {
public:
  HandList(int t, Stone s, int x, int y);
  ~HandList() = default;
  void replay(BoardMaster& board);
  void report(std::ofstream& log_file);
  Stone convert_char_to_stone(char stone_type);
private:
  int turn_;
  char stone_type_;
  int hand_x_;
  int hand_y_;
};

class GameMaster {
public:
  GameMaster(Player* player[]);
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
  BoardMaster board_;
  Player *participant_[2];
  Player *active_player_;
  int turn_;
  int x_, y_;
  std::vector<HandList> hand_list_;
  std::ofstream log_file_;
};

#endif // GAME_MASTER_H_
