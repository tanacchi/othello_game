#include "include/Player_series.h"

extern int global;

enum class Task {
  INIT,
  OP,
  SHOW,
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
  void report();
};

HandList::HandList(int t, Stone s, int x, int y) {
  turn = t; stone = convert_stone_to_char(s); hand_x = x; hand_y = y;
}

void HandList::report() {
  std::cout << "[turn] : " << turn << '\t';
  std::cout << "Stone : " << stone << '\t';
  std::cout << "x = " << hand_x << ",  y = " << hand_y << std::endl;;
}

class GameMaster {
  BoardMaster board;
  Player *participant[2];
  Player *active_player;
  int turn;
  int x, y;
  std::vector<HandList> hand_list;
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
  Task task_ed();
  void record_hand_list();
};

GameMaster::GameMaster(Player* player[])
{
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
  case Task::ED:     return task_ed();
  }
}

Task GameMaster::task_init() {
  turn = 0;
  board.init();
  active_player = participant[0];
  return Task::OP;
}

Task GameMaster::task_op() {
  Stone active_stone = active_player->get_mystone();
  board.set_active_stone(active_stone);
  std::cout << "\t\t\t\tturn " << turn + 1 << std::endl;
  std::cout << "WHITE STONE (O) : " << board.count_stone(Stone::WHITE) << '\n'
            << "BLACK STONE (X) : " << board.count_stone(Stone::BLACK) << '\n' <<std::endl;
  std::cout << "Now is [" << active_player->get_myname() << "] : " << convert_stone_to_char(active_stone)<< std::endl;
  board.put_dot_stone();
  board.show();
  static int pass_turn;
  if (!board.count_stone(Stone::DOT)) { std::cout << "PASS !!!" << std::endl; return (++pass_turn < 2) ? Task::JUDGE : Task::ED; }
  else pass_turn = 0;
  board.remove_dot_stone();
  return Task::SET;
}

Task GameMaster::task_set() {
  active_player->set_hand(board);
  active_player->get_hand(x, y);
  if (board.is_available_position(x, y)) return Task::INSERT;
  else { std::cout << "It's wrong hand !! Try again." << std::endl; return Task::SET; }
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
  //  show_hand_list();
  std::string answer;
  std::cout << "Continue ?? (yes/no)\n>"; 
  std::cin >> answer;
  if (answer == "yes")     return Task::INIT;
  else if (answer == "no") return Task::ED;
  else return Task::ASK;
}

Task GameMaster::task_ed() {
  return Task::ED;
}

void GameMaster::record_hand_list() {
  std::vector<HandList>::iterator p {hand_list.begin()};
  while(p != hand_list.end()) {
    p++->report();
  }
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
  for (int i = 1; i < argc; i++) input_buff.push_back(argv[i]);
  
  Player* player[2];

  player[0] = new HumanPlayer();
  player[1] = new ComputerPlayer();

  GameMaster master(player);
  Task task {Task::INIT};
  while (task != Task::ED) task = master.run(task);
  std::cout << "See you~~\n" << global << std::endl;
  // BoardMaster board;
  // board.init();
  // board.set_active_stone(Stone::WHITE);
  // OthelloAI ai(board, 3);
  
  return 0;
}
