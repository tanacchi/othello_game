#include <iostream>
#include "GameBoard.hpp"
#include "../include/BoardMaster.hpp"

enum class Task {
  Init, Op, Set, Insert, Write, Judge, Switch, Ed
};

Task run(Task task);
Task task_init();
Task task_op();
Task task_set();
Task task_insert();
Task task_write();
Task task_judge();
Task task_switch();

Position size{std::make_pair(10, 10)};
GameBoard board{size};
int turn;
Position current_pos;

Task run(Task task)
{
  switch (task) {
  case Task::Init:   return task_init();
  case Task::Op:     return task_op();
  case Task::Set:    return task_set();
  case Task::Insert: return task_insert();
  case Task::Write:  return task_write();
  case Task::Judge:  return task_judge();
  case Task::Switch: return task_switch();
  case Task::Ed:
  default:           throw std::invalid_argument{"It's wrong task!!"};
  }
}

Task task_init()
{
  turn = 0;
  board.init();
  return Task::Op;
}

Task task_op()
{
  
}

Task task_set()
{

}

Task task_insert()
{

}

Task task_write()
{

}
  
Task task_judge()
{

}

Task task_switch()
{

}

int main()
{
  std::cout << "sizeof(BoardBase) = " << sizeof(BoardBase) << ", "
            << "sizeof(GameBoard) = " << sizeof(GameBoard) << std::endl;
  std::cout << "sizeof(BoardMaster) = " << sizeof(BoardMaster) << std::endl;
  board.show();
  return 0;
}
