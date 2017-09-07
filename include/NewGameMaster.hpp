#ifndef NEW_GAME_MASTER_H_
#define NEW_GAME_MASTER_H_

class NewGameMaster {
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
  NewGameMaster(Player* player[]);
  ~NewGameMaster() = default;
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
//  std::ofstream log_file_;
};

#endif // NEW_GAME_MASTER_H_
