#include "include/BoardBase.h"

BoardBase::BoardBase() {
  board = std::vector<std::vector<Stone> >(BOARD_SIZE, std::vector<Stone>(BOARD_SIZE));
}

void BoardBase::init_board() {
  for (int i = 0; i < board.size(); i++)
    for (int j = 0; j < board.front().size(); j++)
      board[i][j] = Stone::SPACE;
  board[3][3] = board[4][4] = Stone::WHITE;
  board[3][4] = board[4][3] = Stone::BLACK;
}

Stone BoardBase::get_stone(int x, int y) {
  return board[y][x];
}

char convert_stone_to_char(Stone src) {
  switch (src) {
  case Stone::SPACE: return ' ';
  case Stone::BLACK: return 'X';
  case Stone::WHITE: return 'O';
  case Stone::DOT:   return '*';
  }
}

void BoardBase::show_board() {
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

void BoardBase::set_active_stone(Stone stone) {
  active_stone = stone;
}

void BoardBase::insert_stone(int x, int y) {
  board[y][x] = active_stone;
}

void BoardBase::insert_stone(int x, int y, Stone stone) {
  board[y][x] = stone;
}

bool BoardBase::stone_compare(int x, int y, Stone src) {
  return board[y][x] == src;
}

int BoardBase::get_reversible_length(int x, int y, int dx, int dy) {
  Stone enemy_stone = get_enemy(); 
  for (int i = 1; is_inside_board(x + i*dx, y + i*dy); i++) {
    Stone target = board[y + i*dy][x + i*dx];
    if (target == active_stone) return i-1;
    else if (target == enemy_stone) continue;
    else break;
  }
  return 0;
}

bool BoardBase::is_inside_board(int x, int y) {
  return (0 <= x && x < BOARD_SIZE) && (0 <= y && y < BOARD_SIZE);
}

Stone BoardBase::get_enemy() {
  return (active_stone == Stone::WHITE) ? Stone::BLACK : Stone::WHITE;
}

