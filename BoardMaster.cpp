#include "include/BoardMaster.h"

BoardMaster::BoardMaster()
  : board{std::vector<std::vector<Stone> >(BOARD_SIZE, std::vector<Stone >(BOARD_SIZE))}

{
}

void BoardMaster::init() {
  for (size_t i {0}; i < board.size(); i++)
    for (size_t j {0}; j < board.front().size(); j++)
      board[i][j] = Stone::SPACE;
  board[3][3] = board[4][4] = Stone::WHITE;
  board[3][4] = board[4][3] = Stone::BLACK;
}

void BoardMaster::size() {
  std::cout <<  " Hight = "<< board.size() << std::endl;
  std::cout <<  " Width = "<< board.front().size() << std::endl;
}

Stone BoardMaster::get_stone(int x, int y) {
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

void BoardMaster::show() {
  std::cout << "---------------------------" << std::endl;
  std::cout << "  ";
  for (size_t i {0}; i < BOARD_SIZE; i++) std::cout << i+1 << ' ';
  std::cout << std::endl;
  for (size_t i {0}; i < BOARD_SIZE; i++) {
    std::cout << i+1 << ' ';
    for (size_t j {0}; j < BOARD_SIZE; j++) std::cout << convert_stone_to_char(board[i][j]) << ' ';
    std::cout << std::endl;
  }
  std::cout << "---------------------------" << std::endl;
}

void BoardMaster::set_active_stone(Stone stone) {
  active_stone = stone;
}

void BoardMaster::insert(int x, int y) {
  board[y][x] = active_stone;
}

void BoardMaster::insert(int x, int y, Stone stone) {
  board[y][x] = stone;
}

int BoardMaster::get_reversible_length(int x, int y, int dx, int dy) {
  Stone enemy_stone {get_enemy()}; 
  for (size_t i {1}; is_inside_board(x + i*dx, y + i*dy); i++) {
    Stone target {board[y + i*dy][x + i*dx]};
    if (target == active_stone) return i-1;
    else if (target == enemy_stone) continue;
    else break;
  }
  return 0;
}

bool BoardMaster::is_inside_board(int x, int y) {
  return (0 <= x && x < BOARD_SIZE) && (0 <= y && y < BOARD_SIZE);
}

Stone BoardMaster::get_enemy() {
  return (active_stone == Stone::WHITE) ? Stone::BLACK : Stone::WHITE;
}

const int dx[8] = { 0, 1, 1, 1, 0,-1,-1,-1 };
const int dy[8] = {-1,-1, 0, 1, 1, 1, 0,-1 };

bool BoardMaster::is_available_position(int x, int y) {
  return is_inside_board(x, y) && board[y][x] == Stone::SPACE && count_reversible_stone(x, y);
}

bool BoardMaster::can_continue() {
  return count_stone(Stone::SPACE) && count_stone(Stone::BLACK) && count_stone(Stone::WHITE);
}

int BoardMaster::count_stone(Stone target) {
  int count {0};
  for (size_t i {0}; i < BOARD_SIZE; i++)
    for (size_t j {0}; j < BOARD_SIZE; j++)
      if (board[i][j] == target) count++;
  return count;
}

int BoardMaster::count_reversible_stone(int x, int y) {
  int reversible_stone_count {0};
  for (size_t i {0}; i < 8; i++) reversible_stone_count += get_reversible_length(x, y, dx[i], dy[i]);
  return reversible_stone_count;
}

void BoardMaster::reverse_stone(int x, int y) {
  int reverse_length {0};
  for (size_t i {0}; i < 8; i++) {
    reverse_length = get_reversible_length(x, y, dx[i], dy[i]);
    for (size_t j {1}; j <= reverse_length; j++) insert(x + j*dx[i], y + j*dy[i]);
  }
}

void BoardMaster::put_dot_stone() {
  for (size_t i {0}; i < BOARD_SIZE; i++)
    for (size_t j {0}; j < BOARD_SIZE; j++)
      if (is_available_position(j, i)) insert(j, i, Stone::DOT);
}

void BoardMaster::remove_dot_stone() {
  for (size_t i {0}; i< BOARD_SIZE; i++)
    for (size_t j {0}; j < BOARD_SIZE; j++)
      if (board[i][j] == Stone::DOT) insert(j, i, Stone::SPACE);
}

BoardMaster& BoardMaster::operator=(BoardMaster& src) {
  for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
      board[i][j] = src.board[i][j];
  active_stone = src.active_stone;
}
