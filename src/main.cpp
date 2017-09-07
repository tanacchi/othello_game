#include "../include/GameMaster.hpp"

extern int global;

Mode read_mode(std::vector<std::string> user_message)
{
  for (size_t i {0}; i < user_message.size(); i++) std::cout << user_message[i] << std::endl;
  for (size_t i = 0; i < user_message.size(); i++) {
    if (user_message[i] == "--normal") {
      if (++i < user_message.size()) return Mode::False;
      else if (user_message[i] == "human") return Mode::Normal_h;
      else if (user_message[i] == "cpu") return Mode::Normal_c;
    }
    else if(user_message[i] == "--personal") return Mode::Personal;
    else if(user_message[i] == "--auto") return Mode::Auto;
  }
  return Mode::False;
}

void show_usage()
{
  std::cout << '\n'
            << "********************************************************\n"
            << "* [Usage]                                              *\n"
            << "* Options  : --normal <first player (human or cpu)>    *\n"
            << "*            --personal                                *\n"
            << "*            --auto                                    *\n"
            << "********************************************************\n" << std::endl;
}

void reset_message(std::vector<std::string>& user_message)
{
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

void set_player(Mode mode, Player* player[])
{
  switch (mode) {
  case Mode::Normal_h:
    player[0] = new HumanPlayer();
    player[1] = new ComputerPlayer();
    break;
  case Mode::Normal_c:
    player[0] = new ComputerPlayer();
    player[1] = new HumanPlayer();
    break;
  case Mode::Personal:
    player[0] = new HumanPlayer();
    player[1] = new HumanPlayer();
    break;
  case Mode::Auto:
    player[0] = new ComputerPlayer();
    player[1] = new ComputerPlayer();
    break; 
  default:
    player[0] = NULL;
    player[1] = NULL;
  }
}

int main(int argc, char** argv)
{

  // std::vector<std::string> user_message{argv, argv + argc};
  // // for (int i {1}; i < argc; i++) user_message.push_back(argv[i]);

  // Mode mode = Mode::Normal_h;// Mode::False;;
  // // while ((mode = read_mode(user_message)) == Mode::False) {
  // //   show_usage();
  // //   reset_message(user_message);
  // //   for (size_t i = 0; i < user_message.size(); i++) std::cout << user_message[i] << std::endl;
  // // }
  
  // Player* player[2];
  // set_player(mode, player);

  Player* player[2];
  player[0] = new HumanPlayer;
  player[1] = new HumanPlayer;

  GameMaster master(player);
  Task task {Task::Init};
  while (task != Task::Ed) task = master.run(task);

  std::cout << "See you~~\n" << global << std::endl;
  delete* player;
   
  return 0;
}
