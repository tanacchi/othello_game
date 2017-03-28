#include <iostream>
#include <random>

#include <thread>
#include <chrono>

#define BOARD_SIZE 8

enum class STONE {
  WHITE,
  BLACK,
  SPACE,
  DOT
};

class BoardMaster {
  STONE board[BOARD_SIZE][BOARD_SIZE];
  STONE active_stone;
public:
  BoardMaster();
  void init_board();
  void show_board();
  const char convert_num_to_char(STONE stone);
  bool is_stone_space(int x, int y);
  bool is_inside_board(int x, int y);
  bool is_valid_hand(int x, int y);
  void insert_stone(int x, int y); 
  void set_active_stone(STONE stone);
  bool can_continue();
};

BoardMaster::BoardMaster() {
  init_board();
  active_stone = STONE::WHITE;
  show_board();
}

void BoardMaster::init_board() {
  for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
      board[i][j] = STONE::SPACE;
  board[3][3] = board[4][4] = STONE::WHITE;
  board[3][4] = board[4][3] = STONE::BLACK;
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

const char BoardMaster::convert_num_to_char(STONE src) {
  switch (src) {
  case STONE::SPACE: return ' ';
  case STONE::BLACK: return 'O';
  case STONE::WHITE: return 'X';
  case STONE::DOT:   return '*';
  }
}

void BoardMaster::set_active_stone(STONE stone) {
  active_stone = stone;
}

bool BoardMaster::is_inside_board(int x, int y) {
  return (0 <= x && x < BOARD_SIZE) && (0 <= y && y < BOARD_SIZE);
}

bool BoardMaster::is_stone_space(int x, int y) {
  return (board[y][x] == STONE::SPACE);
}

bool BoardMaster::is_valid_hand(int x, int y) {
  return is_inside_board(x, y) && is_stone_space(x, y);
}

void BoardMaster::insert_stone(int x, int y) {
  board[y][x] = active_stone;
}

bool BoardMaster::can_continue() {
  for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
      if (board[i][j] == STONE::SPACE) return true;
  return false;
}

class Player {
  STONE MY_STONE;
  int hand_x, hand_y;
public:
  void set_my_stone(STONE stone);
  void set_hand(const int input_x, const int input_y);
  STONE get_my_stone();
  void get_hand(int &x, int &y);
};

void Player::set_my_stone(STONE stone) {
  MY_STONE = stone;
}

void Player::set_hand(const int input_x, const int input_y) {
  hand_x = input_x;
  hand_y = input_y;
}

STONE Player::get_my_stone() {
  return MY_STONE;
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
  Player *active_player;

  cpu[0].set_my_stone(STONE::WHITE);
  cpu[1].set_my_stone(STONE::BLACK);
    
  int turn;
  while (board.can_continue()) {
    active_player = &cpu[turn % 2];
    board.set_active_stone(active_player->get_my_stone());
    int x, y;
    do {
      cpu[turn % 2].set_hand_random();
      active_player->get_hand(x, y);
    } while (!board.is_valid_hand(x, y));    
    board.insert_stone(x, y);
    board.show_board();
    turn++;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
  
  return 0;
}
