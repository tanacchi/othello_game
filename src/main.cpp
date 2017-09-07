#include "../include/GameMaster.hpp"

int main(int argc, char** argv)
{
  // std::vector<std::string> user_message{argv, argv + argc};

  Player* player[2];
  player[0] = new HumanPlayer;
  player[1] = new HumanPlayer;
  
  GameMaster master(player);
  Task task {Task::Init};
  while (task != Task::Ed) task = master.run(task);

  std::cout << "See you~~" << std::endl;
  delete* player;
   
  return 0;
}
