#include "../include/Player_series.h"

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
  int turn;
  char stone_type;
  int hand_x;
  int hand_y;
public:
  HandList(int t, Stone s, int x, int y);
  void replay(BoardMaster& board);
  void report(std::ofstream& log_file);
  Stone convert_char_to_stone(char stone_type);
};

class GameMaster {
  BoardMaster board;
  Player *participant[2];
  Player *active_player;
  int turn;
  int x, y;
  std::vector<HandList> hand_list;
  std::ofstream log_file;
public:
  GameMaster(Player* player[]);
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
};
