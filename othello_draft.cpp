#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

#define BOARD_SIZE 8

enum class Stone {
  WHITE,
  BLACK,
  SPACE,
  DOT
};

enum class Task {
  INIT,
  OP,
  SHOW,
  SET,
  INSERT,  
  WRITE,
  JUDGE,
  SWITCH,
  ED
};

const int dx[8] = { 0, 1, 1, 1, 0,-1,-1,-1 };
const int dy[8] = {-1,-1, 0, 1, 1, 1, 0,-1 };

/*

TODO : プレイヤー管理の方法を検討
TODO : 石自体を扱うクラスを作成
TODO : パスされたときの後処理

REFACT : 入力部分を設計しなおしてみる

REFACT : BoardMasterの仕事を分担

*/

class BoardMaster {
  Stone board[BOARD_SIZE][BOARD_SIZE];
  Stone active_stone;
public:
  BoardMaster();
  Stone get_enemy_stone();
  bool is_available_position(int x, int y);
  bool is_inside_board(int x, int y);
  const char convert_stone_to_char(Stone stone);
  inline bool can_continue();
  inline bool stone_compare(int x, int y, Stone src);
  int count_reversible_stone(int x, int y);
  int count_stone(Stone target);
  int get_reversible_length(int x, int y, int dx, int dy);
  int get_reversible_length(int* direction);
  void init_board();
  void insert_stone(int x, int y); 
  void put_dot_stone();
  void remove_dot_stone();
  void reverse_stone(int x, int y);
  void set_active_stone(Stone stone);
  void show_board();
};

BoardMaster::BoardMaster() {
  init_board();
  active_stone = Stone::SPACE;
}

void BoardMaster::init_board() {
  for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
      board[i][j] = Stone::SPACE;
  board[3][3] = board[4][4] = Stone::WHITE;
  board[3][4] = board[4][3] = Stone::BLACK;
}

void BoardMaster::show_board() {
  std::cout << "---------------------------" << std::endl;
  std::cout << "  ";
  for (int i = 0; i < BOARD_SIZE; i++) std::cout << i+1 << ' ';
  std::cout << std::endl;
  for (int i = 0; i < BOARD_SIZE; i++) {
    std::cout << i+1 << ' ';
    for (int j = 0; j < BOARD_SIZE; j++) std::cout << convert_stone_to_char(board[i][j]) << ' ';
    std::cout << std::endl;
  }
  std::cout << "---------------------------" << std::endl;
}

const char BoardMaster::convert_stone_to_char(Stone src) {
  switch (src) {
  case Stone::SPACE: return ' ';
  case Stone::BLACK: return 'X';
  case Stone::WHITE: return 'O';
  case Stone::DOT:   return '*';
  }
}

void BoardMaster::set_active_stone(Stone stone) {
  active_stone = stone;
}

inline bool BoardMaster::is_inside_board(int x, int y) {
  return (0 <= x && x <= BOARD_SIZE) && (0 <= y && y < BOARD_SIZE);
}

bool BoardMaster::is_available_position(int x, int y) {
  return is_inside_board(x, y) && stone_compare(x, y, Stone::SPACE) && count_reversible_stone(x, y);
}

void BoardMaster::insert_stone(int x, int y) {
  board[y][x] = active_stone;
}

inline bool BoardMaster::can_continue() {
  return count_stone(Stone::SPACE) && count_stone(Stone::BLACK) && count_stone(Stone::WHITE);
}

bool BoardMaster::stone_compare(int x, int y, Stone src) {
  return board[y][x] == src;
}

int BoardMaster::count_stone(Stone target) {
  int count = 0;
  for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
      if (board[i][j] == target) count++;
  return count;
}

int BoardMaster::count_reversible_stone(int x, int y) {
  int reversible_stone_count = 0;
  for (int i = 0; i < 8; i++) reversible_stone_count += get_reversible_length(x, y, dx[i], dy[i]);
  return reversible_stone_count;
}

int BoardMaster::get_reversible_length(int x, int y, int dx, int dy) {
  Stone enemy_stone = get_enemy_stone(); 
  for (int i = 1; is_inside_board(x + i*dx, y + i*dy); i++) {
    Stone target = board[y + i*dy][x + i*dx];
    if (target == enemy_stone) continue;
    else if (target == active_stone) return i-1;
    else break;
  }
  return 0;
}

void BoardMaster::reverse_stone(int x, int y) {
  int reverse_length = 0;
  for (int i = 0; i < 8; i++) {
    reverse_length = get_reversible_length(x, y, dx[i], dy[i]);
    for (int j = 1; j <= reverse_length; j++) board[y + j*dy[i]][x + j*dx[i]] = active_stone;
  }
}

Stone BoardMaster::get_enemy_stone() {
  return (active_stone == Stone::WHITE) ? Stone::BLACK : Stone::WHITE;
}

void BoardMaster::put_dot_stone() {
  for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
      if (is_available_position(j, i)) board[i][j] = Stone::DOT;
}

void BoardMaster::remove_dot_stone() {
  for (int i = 0; i< BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
      if (board[i][j] == Stone::DOT) board[i][j] = Stone::SPACE;
}

class Player {
  Stone my_stone;
  int hand_x, hand_y;
public:
  void set_my_stone(Stone stone);
  void input_position(const int input_x, const int input_y);
  virtual void set_hand();
  Stone get_my_stone();
  void get_hand(int &x, int &y);
};

void Player::set_my_stone(Stone stone) {
  my_stone = stone;
}

void Player::input_position(const int input_x, const int input_y) {
  hand_x = input_x;
  hand_y = input_y;
}

void Player::set_hand()
{
}

Stone Player::get_my_stone() {
  return my_stone;
}

void Player::get_hand(int &x, int &y) {
  x = hand_x;
  y = hand_y;
}

class HumanPlayer : public Player {
public:
  void set_hand();
};

void HumanPlayer::set_hand() {
  int input_x, input_y;
  std::cout << "First, input 'x' !! \n> "; std::cin >> input_x;
  std::cout << "Next, input 'y' !! \n> ";  std::cin >> input_y;
  input_position(input_x - 1, input_y - 1);
}

class ComputerPlayer : public Player {
  std::mt19937 rand_pos;
public:
  ComputerPlayer();
  void set_hand();
};

ComputerPlayer::ComputerPlayer() : rand_pos { std::random_device{}() }
{ 
}

void ComputerPlayer::set_hand() {
  std::uniform_int_distribution<int> rand100(0, 7);
  int input_x = rand100(rand_pos);
  int input_y = rand100(rand_pos);
  input_position(input_x, input_y);
}

struct HandList {
  int turn;
  Stone stone;
  int x;
  int y;
};

class GameMaster {
  BoardMaster board;
  ComputerPlayer cpu[2];
  Player* active_player;
  int turn;
  int x, y;
  HandList hand_list[];
public:
  Task run(Task mode);
  Task task_init();
  Task task_op();
  Task task_set();
  Task task_insert();
  Task task_write();
  Task task_judge();
  Task task_switch();
  Task task_ed();
  void show_hand_list();
};

Task GameMaster::run(Task mode) {
  switch (mode) {
  case Task::INIT:   return task_init();
  case Task::OP:     return task_op();
  case Task::SET:    return task_set();
  case Task::INSERT: return task_insert();
  case Task::WRITE:  return task_write();
  case Task::JUDGE:  return task_judge();
  case Task::SWITCH: return task_switch();
  case Task::ED:     return task_ed();
  }
}

Task GameMaster::task_init() {
  turn = 0;
  cpu[0].set_my_stone(Stone::WHITE);
  cpu[1].set_my_stone(Stone::BLACK);
  active_player = &cpu[0];
  return Task::OP;
}

Task GameMaster::task_op() {
  board.set_active_stone(active_player->get_my_stone());
  std::cout << "turn " << turn + 1 << std::endl;
  std::cout << "Now is " << board.convert_stone_to_char(active_player->get_my_stone()) << std::endl;
  board.put_dot_stone();
  board.show_board();
  return Task::SET;
}

Task GameMaster::task_set() {
  active_player->set_hand();
  active_player->get_hand(x, y);
  if (!board.count_stone(Stone::DOT)) { std::cout << "PASS !!!" << std::endl; return Task::JUDGE; }
  if (board.stone_compare(x, y, Stone::DOT)) return Task::INSERT;
  else return Task::SET;
}

Task GameMaster::task_insert() {
  board.insert_stone(x, y);
  board.reverse_stone(x, y);
  return Task::WRITE;
}

Task GameMaster::task_write() {
  hand_list[turn].turn = turn + 1;
  hand_list[turn].stone = active_player->get_my_stone();
  hand_list[turn].x = x + 1;
  hand_list[turn].y = y + 1;
  return Task::JUDGE;
}

Task GameMaster::task_judge() {
  board.remove_dot_stone();
  board.show_board();
  std::cout << "\n\n" << std::endl;
  return (board.can_continue()) ? Task::SWITCH : Task::ED;
}

Task GameMaster::task_switch() {
  active_player = &cpu[++turn % 2];
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  return Task::OP;
}

Task GameMaster::task_ed() {
  std::cout << "BLACK STONE : " << board.count_stone(Stone::BLACK) << '\n'
            << "WHITE STONE : " << board.count_stone(Stone::WHITE) << std::endl;
  show_hand_list();
  exit (0);
}

void GameMaster::show_list() {
  for (int i = 0; i <= turn; i++) {
    std::cout << " [turn] " << hand_list[i].turn << '\t';
    std::cout << "Stone : " << board.convert_stone_to_char(hand_list[i].stone);
    std::cout << "  x = " << hand_list[i].x << ", y = " << hand_list[i].y << std::endl;
  }
}

int main() {
  Task mode = Task::INIT;
  GameMaster master;

  while (1)
    mode = master.run(mode);
  
  return 0;
}
