#include "../include/Player_series.h"

extern int global;

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

HandList::HandList(int t, Stone s, int x, int y) {
  turn = t; stone_type = convert_stone_to_char(s); hand_x = x; hand_y = y;
}

void HandList::replay(BoardMaster& board) {
  board.insert(hand_x-1, hand_y-1, convert_char_to_stone(stone_type));
  board.reverse_stone(hand_x-1, hand_y-1);
  board.switch_active_stone();
} 

Stone HandList::convert_char_to_stone(char stone_type) {
  return (stone_type == 'O') ? Stone::WHITE : Stone::BLACK;
}

void HandList::report(std::ofstream& log_file) {
  log_file << turn << ','<< stone_type << ',' << hand_x << ',' << hand_y << std::endl;
}

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

GameMaster::GameMaster(Player* player[]) {
  participant[0] = player[0];
  participant[1] = player[1];
  participant[0]->set_mystone(Stone::WHITE);
  participant[1]->set_mystone(Stone::BLACK);
}

Task GameMaster::run(Task mode) {
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

Task GameMaster::task_init() {
  turn = 0;
  global = 0;
  board.init();
  active_player = participant[0];
  hand_list.erase(hand_list.begin(), hand_list.end());
  return Task::OP;
}

Task GameMaster::task_op() {
  Stone active_stone = active_player->get_mystone();
  board.set_active_stone(active_stone);
  std::cout << "turn " << turn + 1 << std::endl;
  std::cout << "WHITE STONE (O) : " << board.count_stone(Stone::WHITE) << '\n'
            << "BLACK STONE (X) : " << board.count_stone(Stone::BLACK) << '\n' <<std::endl;
  std::cout << "Now is "<< active_player->get_myname() << "'s turn ! : " << convert_stone_to_char(active_stone)<< std::endl;
  board.put_dot_stone();
  board.show();
  static int pass_turn;
  if (!board.count_stone(Stone::DOT)) { std::cout << "PASS !!!" << std::endl; return (++pass_turn < 2) ? Task::JUDGE : Task::ASK; }
  else pass_turn = 0;
  board.remove_dot_stone();
  return Task::SET;
}

Task GameMaster::task_set() {
  if (!active_player->set_hand(board)) return Task::REVERT;
  active_player->get_hand(x, y);
  if (!board.is_available_position(x, y)) { std::cout << "It's wrong hand !! Try again." << std::endl; return Task::SET; }
  return Task::INSERT;
}

Task GameMaster::task_insert() {
  board.insert(x, y);
  board.reverse_stone(x, y);
  return Task::WRITE;
}

Task GameMaster::task_revert() {
  std::string input_buff;
  std::cout << "Set the turn you wanna play back !" << std::endl;
  std::cout << " > " << std::flush;
  std::cin >> input_buff;
  int destination = std::atoi(input_buff.c_str()) - 1;
  if (destination < 0 || turn < destination) { std::cout << "Pardon ?" << std::endl; return Task::SET; }
  hand_list.erase(hand_list.begin() + destination, hand_list.end());
  turn = destination;
  board.init();
  std::vector<HandList>::iterator p_list = hand_list.begin();
  while (p_list != hand_list.end()) p_list++->replay(board);
  active_player = participant[destination%2];
  return Task::OP;
}

Task GameMaster::task_write() {
  hand_list.push_back(HandList(turn+1, active_player->get_mystone(), x+1, y+1));
  return Task::JUDGE;
}

Task GameMaster::task_judge() {
  board.show();
  std::cout << "\n\n" << std::endl;
  return (board.can_continue()) ? Task::SWITCH : Task::ASK;
}

Task GameMaster::task_switch() {
  active_player = participant[++turn % 2];
  //wait(100);
  return Task::OP;
}

Task GameMaster::task_ask() {
  std::cout << "WHITE STONE (O) : " << board.count_stone(Stone::WHITE) << '\n'
            << "BLACK STONE (X) : " << board.count_stone(Stone::BLACK) << '\n' <<std::endl;
  record_hand_list();
  std::string answer;
  std::cout << "Continue ?? (yes/no)\n > " << std::flush; 
  std::cin >> answer;
  return
    (answer == "yes") ? Task::INIT :
    (answer == "no")  ? Task::ED :
    Task::ASK;
}

void GameMaster::record_hand_list() {
  std::string participant_1 = participant[0]->get_myname();
  std::string participant_2 = participant[1]->get_myname();
  log_file.open("log/" + participant_1 + "_vs_" + participant_2 + ".csv", std::ios::app);
  log_file << participant_1 << ",O" << std::endl;
  log_file << participant_2 << ",X" << std::endl;
  log_file << "~~BEGIN~~" << std::endl;
  std::vector<HandList>::iterator p {hand_list.begin()};
  while(p != hand_list.end()) p++->report(log_file);
  log_file << "~~END~~" << std::endl;
  log_file << "WHITE," << board.count_stone(Stone::WHITE) << std::endl;
  log_file << "BLACK," << board.count_stone(Stone::BLACK) << '\n' << std::endl;
  log_file.close();
}

Mode read_mode(std::vector<std::string> user_message) {
  for (size_t i {0}; i < user_message.size(); i++) std::cout << user_message[i] << std::endl;
  for (size_t i = 0; i < user_message.size(); i++) {
    if (user_message[i] == "--normal") {
      if (++i < user_message.size()) return Mode::FALSE;
      else if (user_message[i] == "human") return Mode::NORMAL_H;
      else if (user_message[i] == "cpu") return Mode::NORMAL_C;
    }
    else if(user_message[i] == "--personal") return Mode::PERSONAL;
    else if(user_message[i] == "--auto") return Mode::AUTO;
  }
  return Mode::FALSE;
}

void show_usage() {
  std::cout << '\n'
            << "********************************************************\n"
            << "* [Usage]                                              *\n"
            << "* Options  : --normal <first player (human or cpu)>    *\n"
            << "*            --personal                                *\n"
            << "*            --auto                                    *\n"
            << "********************************************************\n" << std::endl;
}

void reset_message(std::vector<std::string>& user_message) {
  while (true) {
    user_message.shrink_to_fit();
    std::cout << "What is game mode ? (normal / personal / auto)" << std::endl;
    std::cout << "> " << std::flush;
    std::string input_mode;
    std::getline(std::cin, input_mode);
    if (input_mode == "normal") {
      user_message.push_back("--normal");
      std::cout << "Who is the 1st player ? (human / cpu)" << std::endl;
      std::cout << "> " << std::flush;
      std::string input_person;
      std::cin >> input_person;
      std::cout << input_person << std::endl;
      if (input_person == "human")  { user_message.push_back("human"); return; }
      else if (input_person == "cpu") { user_message.push_back("cpu"); return; }
      std::cout << "Pardon ?" << std::endl;
      continue;
    }
    else if (input_mode == "personal") { user_message.push_back("--personal"); return; }
    else if (input_mode == "auto") { user_message.push_back("--auto"); return; }
    std::cout << "Pardon ??" << std::endl;
  }
}

void set_player(Mode mode, Player* player[]) {
  switch (mode) {
  case Mode::NORMAL_H:
    player[0] = new HumanPlayer();
    player[1] = new ComputerPlayer();
    break;
  case Mode::NORMAL_C:
    player[0] = new ComputerPlayer();
    player[1] = new HumanPlayer();
    break;
  case Mode::PERSONAL:
    player[0] = new HumanPlayer();
    player[1] = new HumanPlayer();
    break;
  case Mode::AUTO:
    player[0] = new ComputerPlayer();
    player[1] = new ComputerPlayer();
    break; 
  default:
    player[0] = NULL;
    player[1] = NULL;
  }
}

int main(int argc, char** argv) {

  std::vector<std::string> user_message{argv, argv + argc};
  // for (int i {1}; i < argc; i++) user_message.push_back(argv[i]);

  Mode mode = Mode::NORMAL_H;// Mode::FALSE;;
  // while ((mode = read_mode(user_message)) == Mode::FALSE) {
  //   show_usage();
  //   reset_message(user_message);
  //   for (size_t i = 0; i < user_message.size(); i++) std::cout << user_message[i] << std::endl;
  // }
  
  Player* player[2];
  set_player(mode, player);
  GameMaster master(player);
  Task task {Task::INIT};
  while (task != Task::ED) task = master.run(task);

  std::cout << "See you~~\n" << global << std::endl;
  return 0;
}
