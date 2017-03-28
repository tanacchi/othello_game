#include <iostream>
#include <random>

#include <thread>
#include <chrono>

#define BOARD_SIZE 8

enum class Stone {
  WHITE,
  BLACK,
  SPACE,
  DOT
};

class BoardMaster {
  Stone board[BOARD_SIZE][BOARD_SIZE];
  Stone active_stone;
public:
  BoardMaster();
  void init_board();
  void show_board();
  const char convert_num_to_char(Stone stone);
  bool is_stone_space(int x, int y);
  bool is_inside_board(int x, int y);
  bool is_valid_hand(int x, int y);
  void insert_stone(int x, int y); 
  void set_active_stone(Stone stone);
  bool can_continue();
  int count_reversible_stone(int x, int y);
  int get_reversible_length(int* direction);
  Stone get_enemy_stone();
};

BoardMaster::BoardMaster() {
  init_board();
  active_stone = Stone::WHITE;
  show_board();
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
  for (int i = 0; i < BOARD_SIZE; i++) std::cout << i << ' ';
  std::cout << std::endl;
  for (int i = 0; i < BOARD_SIZE; i++) {
    std::cout << i << ' ';
    for (int j = 0; j < BOARD_SIZE; j++) std::cout << convert_num_to_char(board[i][j]) << ' ';
    std::cout << std::endl;
  }
  std::cout << "---------------------------" << std::endl;
}

const char BoardMaster::convert_num_to_char(Stone src) {
  switch (src) {
  case Stone::SPACE: return ' ';
  case Stone::BLACK: return 'O';
  case Stone::WHITE: return 'X';
  case Stone::DOT:   return '*';
  }
}

void BoardMaster::set_active_stone(Stone stone) {
  active_stone = stone;
}

inline bool BoardMaster::is_inside_board(int x, int y) {
  return (0 <= x && x < BOARD_SIZE) && (0 <= y && y < BOARD_SIZE);
}

bool BoardMaster::is_stone_space(int x, int y) {
  return (board[y][x] == Stone::SPACE);
}

bool BoardMaster::is_valid_hand(int x, int y) {
  return is_inside_board(x, y) && is_stone_space(x, y);
}

void BoardMaster::insert_stone(int x, int y) {
  board[y][x] = active_stone;
}

bool BoardMaster::can_continue() {
  int count_space, count_black, count_white = 0;
  for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++) 
      switch (board[i][j]) {
      case Stone::SPACE: count_space++; break;
      case Stone::BLACK: count_black++; break;
      case Stone::WHITE: count_white++; break;
      }
  return (count_space && count_black && count_white);
}

int BoardMaster::count_reversible_stone(int x, int y) {
  Stone enemy_stone = get_enemy_stone();
  int reversible_stone_count;
  int dx[8] = { 0, 1, 1, 1, 0,-1,-1,-1 };
  int dy[8] = { 1, 1, 0,-1,-1,-1, 0, 1 };
  
  for (int i = 0; i < 8; i++) {
    for (int j = 0; is_inside_board(x + j*dx[i], y + j*dy[i]); j++) {
      Stone target = board[y + j*dy[i]][x + j*dx[i]];
      if (target == enemy_stone) continue; 
      else if (target == active_stone) { reversible_stone_count += j; break; }
      else break;
    }
  }
  return reversible_stone_count;
}

Stone BoardMaster::get_enemy_stone() {
  return (active_stone == Stone::WHITE) ? Stone::BLACK : Stone::WHITE;
}

class Player {
  Stone MY_Stone;
  int hand_x, hand_y;
public:
  void set_my_stone(Stone stone);
  void set_hand(const int input_x, const int input_y);
  Stone get_my_stone();
  void get_hand(int &x, int &y);
};

void Player::set_my_stone(Stone stone) {
  MY_Stone = stone;
}

void Player::set_hand(const int input_x, const int input_y) {
  hand_x = input_x;
  hand_y = input_y;
}

Stone Player::get_my_stone() {
  return MY_Stone;
}

void Player::get_hand(int &x, int &y) {
  x = hand_x;
  y = hand_y;
}

class HumanPlayer : public Player {
public:
  void set_hand_console();
};

void HumanPlayer::set_hand_console() {
  int input_x, input_y;
  std::cout << "First, input 'x' !! \n> "; std::cin >> input_x;
  std::cout << "Next, input 'y' !! \n> ";  std::cin >> input_y;
  set_hand(input_x, input_y);
}

class ComputerPlayer : public Player {
public:
  void set_hand_random();
};

void ComputerPlayer::set_hand_random() {
  std::random_device rnd;
  std::mt19937 random_x(rnd()), random_y(rnd());
  std::uniform_int_distribution<> rand100(0, 9);
  int input_x = rand100(random_x);
  int input_y = rand100(random_y);
  set_hand(input_x, input_y);
}

int main() {

  BoardMaster board;
  ComputerPlayer cpu[2];

  cpu[0].set_my_stone(Stone::WHITE);
  cpu[1].set_my_stone(Stone::BLACK);
    
  int turn;
  while (board.can_continue()) {
    board.set_active_stone(cpu[turn % 2].get_my_stone());

    int x, y;
    do {
      cpu[turn % 2].set_hand_random();
      cpu[turn % 2].get_hand(x, y);
    } while (!board.is_valid_hand(x, y));
    
    int reversible_stone = board.count_reversible_stone(x, y);
    std::cout << "reversible_stone = " << reversible_stone << std::endl;
    board.insert_stone(x, y);
    board.show_board();
    turn++;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }   
  return 0;
}
