#include <iostream>
#include "../src/GameBoard.hpp"
#include "../include/BoardMaster.hpp"

enum class Task {
  Init, Op, Set, Insert, Judge, Switch, Ed
};

Task run(Task task);
Task task_init();
Task task_op();
Task task_set();
Task task_insert();
Task task_judge();
Task task_switch();

Task phase{Task::Init};
BoardBase::Position size{10, 10};
GameBoard board{size};
int turn;
BoardBase::Position current_pos{0, 0};

Task run(Task task)
{
  switch (task) {
  case Task::Init:   return task_init();
  case Task::Op:     return task_op();
  case Task::Set:    return task_set();
  case Task::Insert: return task_insert();
  case Task::Judge:  return task_judge();
  case Task::Switch: return task_switch();
  case Task::Ed:
  default:           throw std::invalid_argument{"It's wrong task!!"};
  }
}

Task task_init()
{
  turn = 1;
  board.init();
  return Task::Op;
}

Task task_op()
{
  std::cout << "turn : " << turn << std::endl;
  board.put_dots();
  board.show();
  board.remove_dots();
  return Task::Set;
}

Task task_set()
{
  short input_x, input_y;
  std::cout << "Input hand\n x = " << std::flush;
  std::cin >> input_x;
  std::cout << "\x1b[1A\x1b[8C" << std::flush;
  std::cout << "y = " << std::flush;
  std::cin >> input_y;
  current_pos.x = static_cast<PlaneVector::Point>(input_x-1);
  current_pos.y = static_cast<PlaneVector::Point>(input_y-1);
  return board.is_available_position(current_pos) ? Task::Insert : Task::Set;
}

Task task_insert()
{
  board.insert(BoardBase::Position{5, 3});
  board.insert(current_pos);
  board.reverse(current_pos);
  board.show();
  return Task::Judge;
}
  
Task task_judge()
{
  if (!board.can_continue()) return Task::Ed;
  return Task::Switch;
}

Task task_switch()
{
  ++turn;
  board.switch_active_stone();
  return Task::Op;
}

int main()
{
  std::cout << "sizeof(BoardBase) = " << sizeof(BoardBase) << ", "
            << "sizeof(GameBoard) = " << sizeof(GameBoard) << std::endl;
  std::cout << "sizeof(BoardMaster) = " << sizeof(BoardMaster) << std::endl;
  while (phase != Task::Ed)
    phase = run(phase);
  return 0;
}
