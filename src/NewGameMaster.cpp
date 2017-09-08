#include "../include/NewGameMaster.hpp"

NewGameMaster::NewGameMaster(PlaneVector board_size, Player* player[])
  : board_{board_size},
    participant_{player[0], player[1]},
    active_player_{participant_[0]},
    turn_{0},
    pos_{-1, -1}
//    hand_list_{}
//    log_file_      {}
{
}

NewGameMaster::Task NewGameMaster::run(Task mode)
{
  switch (mode) {
  case Task::Init:   return task_init();
  case Task::Op:     return task_op();
  case Task::Set:    return task_set();
  case Task::Insert: return task_insert();
  case Task::Revert: return task_revert();
  case Task::Write:  return task_write();
  case Task::Judge:  return task_judge();
  case Task::Switch: return task_switch();
  case Task::Ask:    return task_ask();
  case Task::Ed:
  default:           return Task::Ed;
  }
}

NewGameMaster::Task NewGameMaster::task_init()
{
  board_.init();
  active_player_ = participant_[0];
  turn_ = 0;
//  hand_list_.clear();
  return Task::Op;
}
  
NewGameMaster::Task NewGameMaster::task_op()
{
  std::cout << "turn : " << turn_ + 1 << std::endl;
  board_.put_dots();
  board_.show();
  static int pass_turn;
  if (!board_.count_stone(BoardSeries::Stone::Dot)) { std::cout << "PASS !!!" << std::endl; return (++pass_turn < 2) ? Task::Judge : Task::Ask; }
  else pass_turn = 0;
  board_.remove_dots();
  return Task::Set;
}

NewGameMaster::Task NewGameMaster::task_set()
{
//  if (!active_player_->set_hand(board_)) return Task::Revert;
  active_player_->set_hand(board_);
  pos_ = active_player_->get_hand();
  if (!board_.is_available_position(pos_)) {
    std::cout << "It's wrong hand !! Try again." << std::endl;
    return Task::Set;
  }
  return Task::Insert;
}

NewGameMaster::Task NewGameMaster::task_insert()
{
  board_.insert(pos_);
  board_.reverse(pos_);
  return Task::Judge;
}

NewGameMaster::Task NewGameMaster::task_revert()
{
  return Task::Ed;
}

NewGameMaster::Task NewGameMaster::task_write()
{
  return Task::Ed;
}

NewGameMaster::Task NewGameMaster::task_judge()
{
  board_.show();
  return (board_.can_continue()) ? Task::Switch : Task::Ask;
}

NewGameMaster::Task NewGameMaster::task_switch()
{
  ++turn_;
  active_player_ = participant_[turn_ % 2];
  return Task::Op;
}

NewGameMaster::Task NewGameMaster::task_ask()
{
  std::cout << "WHITE STONE (O) : " << board_.count_stone(BoardSeries::Stone::White) << '\n'
            << "BLACK STONE (X) : " << board_.count_stone(BoardSeries::Stone::Black) << '\n'
            <<std::endl;
  std::cout << "Continue ?? (yes/no)\n > " << std::flush;
  std::string answer;
  std::cin >> answer;
  return
    (answer == "yes") ? Task::Init :
    (answer == "no")  ? Task::Ed :
    Task::Ask;
}

void NewGameMaster::record_hand_list()
{
}
