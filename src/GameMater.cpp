#include "../include/GameMaster.hpp"

extern int global;

HandList::HandList(int turn, Stone stone, int hand_x, int hand_y)
  : turn_{turn},
    stone_type_{convert_stone_to_char(stone)},
    hand_x_{hand_x},
    hand_y_{hand_y}
{
}

void HandList::replay(BoardMaster& board)
{
  board.insert(hand_x_-1, hand_y_-1, convert_char_to_stone(stone_type_));
  board.reverse_stone(hand_x_-1, hand_y_-1);
  board.switch_active_stone();
} 

Stone HandList::convert_char_to_stone(char stone_type)
{
  return (stone_type == 'O') ? Stone::WHITE : Stone::BLACK;
}

void HandList::report(std::ofstream& log_file)
{
  log_file << turn_ << ','<< stone_type_ << ',' << hand_x_ << ',' << hand_y_ << std::endl;
}

GameMaster::GameMaster(Player* player[])
  : participant_ {player[0], player[1]}
{
  participant_[0]->set_mystone(Stone::WHITE);
  participant_[1]->set_mystone(Stone::BLACK);
}

Task GameMaster::run(Task mode)
{
  switch (mode) {
  case Task::INIT:   return task_init();
  case Task::OP:     return task_op();
  case Task::SET:    return task_set();
  case Task::INSERT: return task_insert();
  case Task::REVERT: return task_revert();
  case Task::WRITE:  return task_write();
  case Task::JUDGE:  return task_judge();
  case Task::SWITCH: return task_switch();
  case Task::ASK:    return task_ask();
  case Task::ED:
  default:           return Task::ED;
  }
}

Task GameMaster::task_init()
{
  turn_ = 0;
  global = 0;
  board_.init();
  active_player_ = participant_[0];
  hand_list_.erase(hand_list_.begin(), hand_list_.end());
  return Task::OP;
}

Task GameMaster::task_op()
{
  Stone active_stone = active_player_->get_mystone();
  board_.set_active_stone(active_stone);
  std::cout << "turn " << turn_ + 1 << std::endl;
  std::cout << "WHITE STONE (O) : " << board_.count_stone(Stone::WHITE) << '\n'
            << "BLACK STONE (X) : " << board_.count_stone(Stone::BLACK) << '\n' <<std::endl;
  std::cout << "Now is "<< active_player_->get_myname() << "'s turn ! : " << convert_stone_to_char(active_stone)<< std::endl;
  board_.put_dot_stone();
  board_.show();
  static int pass_turn;
  if (!board_.count_stone(Stone::DOT)) { std::cout << "PASS !!!" << std::endl; return (++pass_turn < 2) ? Task::JUDGE : Task::ASK; }
  else pass_turn = 0;
  board_.remove_dot_stone();
  return Task::SET;
}

Task GameMaster::task_set()
{
  if (!active_player_->set_hand(board_)) return Task::REVERT;
  active_player_->get_hand(x_, y_);
  if (!board_.is_available_position(x_, y_)) { std::cout << "It's wrong hand !! Try again." << std::endl; return Task::SET; }
  return Task::INSERT;
}

Task GameMaster::task_insert()
{
  board_.insert(x_, y_);
  board_.reverse_stone(x_, y_);
  return Task::WRITE;
}

Task GameMaster::task_revert()
{
  std::string input_buff;
  std::cout << "Set the turn you wanna play back !" << std::endl;
  std::cout << " > " << std::flush;
  std::cin >> input_buff;
  int destination = std::atoi(input_buff.c_str()) - 1;
  if (destination < 0 || turn_ < destination) { std::cout << "Pardon ?" << std::endl; return Task::SET; }
  hand_list_.erase(hand_list_.begin() + destination, hand_list_.end());
  turn_ = destination;
  board_.init();
  std::vector<HandList>::iterator p_list = hand_list_.begin();
  while (p_list != hand_list_.end()) p_list++->replay(board_);
  active_player_ = participant_[destination%2];
  return Task::OP;
}

Task GameMaster::task_write()
{
  hand_list_.push_back(HandList(turn_+1, active_player_->get_mystone(), x_+1, y_+1));
  return Task::JUDGE;
}

Task GameMaster::task_judge()
{
  board_.show();
  std::cout << "\n\n" << std::endl;
  return (board_.can_continue()) ? Task::SWITCH : Task::ASK;
}

Task GameMaster::task_switch()
{
  active_player_ = participant_[++turn_ % 2];
  //wait(100);
  return Task::OP;
}

Task GameMaster::task_ask()
{
  std::cout << "WHITE STONE (O) : " << board_.count_stone(Stone::WHITE) << '\n'
            << "BLACK STONE (X) : " << board_.count_stone(Stone::BLACK) << '\n' <<std::endl;
  record_hand_list();
  std::string answer;
  std::cout << "Continue ?? (yes/no)\n > " << std::flush; 
  std::cin >> answer;
  return
    (answer == "yes") ? Task::INIT :
    (answer == "no")  ? Task::ED :
    Task::ASK;
}

void GameMaster::record_hand_list()
{
  std::string participant_1 = participant_[0]->get_myname();
  std::string participant_2 = participant_[1]->get_myname();
  log_file_.open("log/" + participant_1 + "_vs_" + participant_2 + ".csv", std::ios::app);
  log_file_ << participant_1 << ",O" << std::endl;
  log_file_ << participant_2 << ",X" << std::endl;
  log_file_ << "~~BEGIN~~" << std::endl;
  std::vector<HandList>::iterator p {hand_list_.begin()};
  while(p != hand_list_.end()) p++->report(log_file_);
  log_file_ << "~~END~~" << std::endl;
  log_file_ << "WHITE," << board_.count_stone(Stone::WHITE) << std::endl;
  log_file_ << "BLACK," << board_.count_stone(Stone::BLACK) << '\n' << std::endl;
  log_file_.close();
}
