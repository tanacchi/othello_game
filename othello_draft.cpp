#include <iostream>
#include <random>

#define BOARD_SIZE 8

#define HAND_X 0
#define HAND_Y 1

enum class STONE {
  SPACE,
  BLACK,
  WHITE,
  DOT
};

class Board_Master {
  STONE board[BOARD_SIZE][BOARD_SIZE];
  STONE active_stone;
public:
  Board_Master();
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

Board_Master::Board_Master() {
  init_board();
  active_stone = STONE::WHITE;
  show_board();
}

void Board_Master::init_board() {
  for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
      board[i][j] = STONE::SPACE;
  board[3][3] = board[4][4] = STONE::WHITE;
  board[3][4] = board[4][3] = STONE::BLACK;
}

void Board_Master::show_board() {
  std::cout << "  ";
  for (int i = 0; i < BOARD_SIZE; i++) std::cout << i << ' ';
  std::cout << std::endl;
  for (int i = 0; i < BOARD_SIZE; i++) {
    std::cout << i << ' ';
    for (int j = 0; j < BOARD_SIZE; j++) std::cout << convert_num_to_char(board[i][j]) << ' ';
    std::cout << std::endl;
  }
}

const char Board_Master::convert_num_to_char(STONE src) {
  switch (src) {
  case STONE::SPACE: return ' ';
  case STONE::BLACK: return 'O';
  case STONE::WHITE: return 'X';
  case STONE::DOT:   return '*';
  }
}

void Board_Master::set_active_stone(STONE stone) {
  active_stone = stone;
}

bool Board_Master::is_inside_board(int x, int y) {
  return (0 <= x && x < BOARD_SIZE) && (0 <= y && y < BOARD_SIZE);
}

bool Board_Master::is_stone_space(int x, int y) {
  return (board[y][x] == STONE::SPACE);
}

bool Board_Master::is_valid_hand(int x, int y) {
  return is_inside_board(x, y) && is_stone_space(x, y);
}

void Board_Master::insert_stone(int x, int y) {
  board[y][x] = active_stone;
}

bool Board_Master::can_continue() {
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

class Human_Player : public Player {
public:
  Human_Player(STONE stone);
  void set_hand_console();
};

Human_Player::Human_Player(STONE stone) {
  set_my_stone(stone);
}

void Human_Player::set_hand_console() {
  int input_x, input_y;
  std::cout << "First, input 'x' !! \n> "; std::cin >> input_x;
  std::cout << "Next, input 'y' !! \n> ";  std::cin >> input_y;
  set_hand(input_x, input_y);
}

class Computer_Player : public Player {
public:
  Computer_Player(STONE stone);
  void set_hand_random();
};

Computer_Player::Computer_Player(STONE stone) {
  set_my_stone(stone);
}

void Computer_Player::set_hand_random() {
  std::random_device rnd;
  std::mt19937 random_x(rnd()), random_y(rnd());
  std::uniform_int_distribution<> rand100(0, 9);
  int input_x = rand100(random_x);
  int input_y = rand100(random_y);
  set_hand(input_x, input_y);
}

int main() {

  Board_Master board;
  Human_Player human(STONE::BLACK);
  Computer_Player cpu(STONE::WHITE);

  Player *active_player = &human;
  
  int x, y;
  int count = 0;
  while (board.can_continue()) {
    do {
      if (count % 2) { active_player = &human; human.set_hand_console(); }
      else { active_player = &cpu; cpu.set_hand_random(); }
      active_player->get_hand(x, y);
      board.set_active_stone(active_player->get_my_stone());
    } while (!board.is_valid_hand(x, y));

    board.insert_stone(x, y);
    if(count % 2) board.show_board();
    count++;
  }
  
  return 0;
}
