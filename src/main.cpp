#include "../include/GameMaster.hpp"

int main(int argc, char** argv)
{
  // std::vector<std::string> user_message{argv, argv + argc};

  Player* player[2];
  player[0] = new ComputerPlayer(3);
  player[1] = new ComputerPlayer(4);

  PlaneVector board_size{8, 8};
  GameMaster master(board_size, player);
  GameMaster::Task task {GameMaster::Task::Init};
  while (task != GameMaster::Task::Ed) task = master.run(task);

  std::cout << "See you~~" << std::endl;
  delete* player;
   
  return 0;
}
