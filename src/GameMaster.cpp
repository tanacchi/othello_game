#include "../include/GameMaster.hpp"

HandList::HandList(short turn, BoardSeries::Stone stone, BoardSeries::Position position)
  : turn_{turn},
    stone_{stone},
    position_{position}
{
}

void HandList::rewrite(BoardSeries::GameBoard& game_board) const
{
  game_board.insert(position_, stone_);
  game_board.reverse(position_);
  game_board.switch_active_stone();   // ここで？
}

void HandList::report(std::ofstream& log_file) const
{
  log_file << turn_ + 1 << ','
           << BoardSeries::to_char(stone_) << ','
           << static_cast<short>(position_.x + 1) << ','
           << static_cast<short>(position_.y + 1) << std::endl;
}

GameMaster::GameMaster(Vector2D board_size, Player* player[])
  : board_        {board_size},
    participant_  {player[0], player[1]},
    active_player_{participant_[0]},
    turn_         {0},
    pos_          {-1, -1},
    hand_list_    {},
    log_file_     {}
{
}

GameMaster::Task GameMaster::run(Task mode)
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

GameMaster::Task GameMaster::task_init()
{
  board_.init();
  active_player_ = participant_[0];
  turn_ = 0;
  hand_list_.clear();
  return Task::Op;
}
  
GameMaster::Task GameMaster::task_op()
{
  std::cout << "turn : " << turn_ + 1 << std::endl;
  board_.put_dots();
  show(board_);
  static int pass_turn;
  if (!board_.count_stone(BoardSeries::Stone::Dot)) { std::cout << "PASS !!!" << std::endl; return (++pass_turn < 2) ? Task::Judge : Task::Ask; }
  else pass_turn = 0;
  board_.remove_dots();
  return Task::Set;
}

GameMaster::Task GameMaster::task_set()
{
  try {
    active_player_->set_hand(board_);
  }
  catch (std::string src) {
    if (src == "revert") return Task::Revert;
  }
  pos_ = active_player_->get_hand();
  if (board_.is_available_position(pos_)) return Task::Insert;
  std::cout << "It's invalid hand !! Try again." << std::endl;
  return Task::Set;
}

GameMaster::Task GameMaster::task_insert()
{
  board_.insert(pos_);
  board_.reverse(pos_);
  return Task::Write;
}

GameMaster::Task GameMaster::task_revert()
{
  std::string input_buff;
  std::cout << "Set the turn you wanna play back !" << std::endl;
  std::cout << " > " << std::flush;
  std::cin >> input_buff;
  short destination = std::atoi(input_buff.c_str()) - 1;
  if (destination < 0 || turn_ < destination) {
    std::cout << "Pardon ?" << std::endl; return Task::Set;
  }
  hand_list_.erase(hand_list_.begin() + destination, hand_list_.end());
  board_.init();
  for (const auto& hl : hand_list_) hl.rewrite(board_);
  active_player_ = participant_[destination%2];
  turn_ = destination;
  return Task::Op;
}

GameMaster::Task GameMaster::task_write()
{
  hand_list_.push_back(HandList(turn_, board_.get_active_stone(), pos_)); // !!!
  return Task::Judge;
}

GameMaster::Task GameMaster::task_judge()
{
  show(board_);
  return (board_.can_continue()) ? Task::Switch : Task::Ask;
}

GameMaster::Task GameMaster::task_switch()
{
  ++turn_;
  active_player_ = participant_[turn_ % 2];
  board_.switch_active_stone();
  return Task::Op;
}

GameMaster::Task GameMaster::task_ask()
{
  std::cout << "WHITE STONE (O) : " << board_.count_stone(BoardSeries::Stone::White) << '\n'
            << "BLACK STONE (X) : " << board_.count_stone(BoardSeries::Stone::Black) << '\n'
            <<std::endl;
  record_hand_list();
  std::cout << "Continue ?? (yes/no)\n > " << std::flush;
  std::string answer;
  std::cin >> answer;
  return
    (answer == "yes") ? Task::Init :
    (answer == "no")  ? Task::Ed :
    Task::Ask;
}

void GameMaster::record_hand_list()
{
  const std::string participant_1 = participant_[0]->get_myname();
  const std::string participant_2 = participant_[1]->get_myname();
  log_file_.open("log/"+participant_1+"_vs_"+participant_2+".csv", std::ios::app);
  log_file_ << participant_1 << ",O" << std::endl;
  log_file_ << participant_2 << ",X" << std::endl;
  log_file_ << "~~BEGIN~~" << std::endl;
  for (const auto& hl : hand_list_) hl.report(log_file_); 
  log_file_ << "~~END~~" << std::endl;
  log_file_ << "WHITE," << board_.count_stone(BoardSeries::Stone::White) << std::endl;
  log_file_ << "BLACK," << board_.count_stone(BoardSeries::Stone::Black) << '\n' << std::endl;
  log_file_.close();

}
