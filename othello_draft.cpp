#include <iostream>

#define BOARD_SIZE 8

enum class STONE {
  SPACE,
  BLACK,
  WHITE,
  DOT
};

class board_master_t {
  STONE board[BOARD_SIZE][BOARD_SIZE];
public:
  board_master_t();
  void init_board();
  void show_board();
  const char convert_num_to_char(STONE ch);
  bool is_stone_space(int x, int y);
  bool is_inside_board(int x, int y);
  void insert_stone(int x, int y); // position & What stone
};

int main() {

  board_master_t board_master;

  board_master.show_board();
  
  return 0;
}

board_master_t::board_master_t() {
  init_board();
}

void board_master_t::init_board() {
  for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
      board[i][j] = STONE::SPACE;
}

void board_master_t::show_board() {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) std::cout << convert_num_to_char(board[i][j]) << ' ';
    std::cout << '\n' ;
  }
}

const char board_master_t::convert_num_to_char(STONE src) {
  switch (src) {
  case STONE::SPACE: return ' ';
  case STONE::BLACK: return 'O';
  case STONE::WHITE: return 'X';
  case STONE::DOT  : return '*';
  }
}

bool board_master_t::is_inside_board(int x, int y) {
  return (0 <= x && x < BOARD_SIZE) && (0 <= y && y < BOARD_SIZE);
}

bool board_master_t::is_stone_space(int x, int y) {
  return (board[y][x] == STONE::SPACE);
}
