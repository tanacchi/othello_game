#include "../include/GameMaster.hpp"

int main(int argc, char** argv)
{
  // std::vector<std::string> user_message{argv, argv + argc};

  Player* player[2];
  player[0] = new HumanPlayer;
  player[1] = new HumanPlayer;

  PlaneVector board_size{6, 6};
  NewGameMaster master(board_size, player);
  NewGameMaster::Task task {NewGameMaster::Task::Init};
  while (task != NewGameMaster::Task::Ed) task = master.run(task);

  std::cout << "See you~~" << std::endl;
  delete* player;
   
  return 0;
}
