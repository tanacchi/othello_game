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

const int dx[8] = { 0, 1, 1, 1, 0,-1,-1,-1 };
const int dy[8] = {-1,-1, 0, 1, 1, 1, 0,-1 };

class BoardMaster {
  Stone board[BOARD_SIZE][BOARD_SIZE]; // TODO: 座標記録
  Stone active_stone;
public:
  BoardMaster();
  void init_board();
  void show_board();
  const char convert_stone_to_char(Stone stone);
  bool is_stone_space(int x, int y);
  bool is_inside_board(int x, int y);
  bool is_available_position(int x, int y);
  bool is_valid_hand(int x, int y);                   // !!!!
  bool stone_compare(int x, int y, Stone src);        // !!!!
  void insert_stone(int x, int y); 
  void set_active_stone(Stone stone);
  inline bool can_continue();
  int count_reversible_stone(int x, int y);
  int get_reversible_length(int* direction);
  Stone get_enemy_stone();
  void put_dot_stone();
  void remove_dot_stone();
  void reverse_stone(int x, int y);
  int count_stone(Stone target);
  int get_reversible_length(int x, int y, int dx, int dy);
};

BoardMaster::BoardMaster() {
  init_board();
  active_stone = Stone::WHITE;
  show_board();
  std::cout << '\n' << std::endl;
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
  return (0 <= x && x < BOARD_SIZE) && (0 <= y && y < BOARD_SIZE);
}

bool BoardMaster::is_stone_space(int x, int y) {
  return (board[y][x] == Stone::SPACE);
}

bool BoardMaster::is_available_position(int x, int y) {
  return is_inside_board(x, y) && is_stone_space(x, y) && count_reversible_stone(x, y);
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

bool BoardMaster::is_valid_hand(int x, int y) {
  return board[y][x] == Stone::DOT;
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
    else return 0;
  }
}

void BoardMaster::reverse_stone(int x, int y) {
  int reverse_length;
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
    std::cout << "turn " << turn + 1 << std::endl;
    std::cout << "Now is " << board.convert_stone_to_char(cpu[turn % 2].get_my_stone()) << std::endl;
    board.put_dot_stone();
    board.show_board();
    int x, y;
    do {
      if (!board.count_stone(Stone::DOT)) {
        std::cout << "!!!!!!! " << board.convert_stone_to_char(cpu[turn % 2].get_my_stone()) <<" was passed !!!!!!!!!!!!" << std::endl;
        break;
      }
      cpu[turn % 2].set_hand_random();
      cpu[turn % 2].get_hand(x, y);
    } while (!board.is_valid_hand(x, y));
    std::cout << "[reversed stone] = " << board.count_reversible_stone(x, y) << std::endl;
    board.insert_stone(x, y);
    board.reverse_stone(x, y);
    board.remove_dot_stone();
    board.show_board();
    std::cout << "\n\n" << std::endl;
    turn++;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  std::cout << "BLACK STONE : " << board.count_stone(Stone::BLACK) << '\n'
            << "WHITE STONE : " << board.count_stone(Stone::WHITE) << std::endl;
  return 0;
}
