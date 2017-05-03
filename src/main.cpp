#include "../include/Player_series.h"

extern int global;

enum class Task {
  INIT,
  OP,
  SET,
  INSERT,  
  WRITE,
  JUDGE,
  SWITCH,
  ASK,
  ED
};

class HandList {
  int turn;
  char stone;
  int hand_x;
  int hand_y;
public:
  HandList(int t, Stone s, int x, int y);
  void report(std::ofstream& log);
};

HandList::HandList(int t, Stone s, int x, int y) {
  turn = t; stone = convert_stone_to_char(s); hand_x = x; hand_y = y;
}

void HandList::report(std::ofstream& log_file) {
  log_file << turn << ','<< stone << ',' << hand_x << ',' << hand_y << std::endl;
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
  // std::cout << global << std::endl;
  std::cout << "WHITE STONE (O) : " << board.count_stone(Stone::WHITE) << '\n'
            << "BLACK STONE (X) : " << board.count_stone(Stone::BLACK) << '\n' <<std::endl;
  std::cout << "Now is [" << active_player->get_myname() << "] : " << convert_stone_to_char(active_stone)<< std::endl;
  board.put_dot_stone();
  board.show();
  static int pass_turn;
  if (!board.count_stone(Stone::DOT)) { std::cout << "PASS !!!" << std::endl; return (++pass_turn < 2) ? Task::JUDGE : Task::ASK; }
  else pass_turn = 0;
  board.remove_dot_stone();
  return Task::SET;
}

Task GameMaster::task_set() {
  active_player->set_hand(board);
  active_player->get_hand(x, y);
  if (!board.is_available_position(x, y)) { std::cout << "It's wrong hand !! Try again." << std::endl; return Task::SET; }
  return Task::INSERT;
}

Task GameMaster::task_insert() {
  board.insert(x, y);
  board.reverse_stone(x, y);
  return Task::WRITE;
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
  if (answer == "yes")     return Task::INIT;
  else if (answer == "no") return Task::ED;
  return Task::ASK;
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

void show_usage() {
  std::cout << '\n'
            << "***************************************************************************************\n"
            << "* [Usage]                                                                             *\n"
            << "* Options  : --normal <first player (human or cpu)>（通常のコンピューターとの対戦）   *\n"
            << "*            --personal（２人での対人戦）                                             *\n"
            << "*            --auto（コンピューター同士での自動プレイ）                               *\n"
            << "***************************************************************************************\n" << std::endl;
}

int main(int argc, char** argv) {
  std::vector<std::string> input_buff;
  for (int i {1}; i < argc; i++) input_buff.push_back(argv[i]);
  for (size_t i {0}; i < input_buff.size(); i++) std::cout << input_buff[i] << std::endl;

  show_usage();
  
  Player* player[2];
  player[0] = new HumanPlayer();
  player[1] = new ComputerPlayer();

  GameMaster master(player);
  Task task {Task::INIT};
  while (task != Task::ED) task = master.run(task);

  std::cout << "See you~~\n" << global << std::endl;
  return 0;
}