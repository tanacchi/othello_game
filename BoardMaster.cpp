#include "include/BoardMaster.h"

const int dx[8] = { 0, 1, 1, 1, 0,-1,-1,-1 };
const int dy[8] = {-1,-1, 0, 1, 1, 1, 0,-1 };

bool BoardMaster::is_available_position(int x, int y) {
  return is_inside_board(x, y) && stone_compare(x, y, Stone::SPACE) && count_reversible_stone(x, y);
}

bool BoardMaster::can_continue() {
  return count_stone(Stone::SPACE) && count_stone(Stone::BLACK) && count_stone(Stone::WHITE);
}

int BoardMaster::count_stone(Stone target) {
  int count {0};
  for (size_t i {0}; i < BOARD_SIZE; i++)
    for (size_t j {0}; j < BOARD_SIZE; j++)
      if (stone_compare(j, i, target)) count++;
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
    for (size_t j {1}; j <= reverse_length; j++) insert_stone(x + j*dx[i], y + j*dy[i]);
  }
}

void BoardMaster::put_dot_stone() {
  for (size_t i {0}; i < BOARD_SIZE; i++)
    for (size_t j {0}; j < BOARD_SIZE; j++)
      if (is_available_position(j, i)) insert_stone(j, i, Stone::DOT);
}

void BoardMaster::remove_dot_stone() {
  for (size_t i {0}; i< BOARD_SIZE; i++)
    for (size_t j {0}; j < BOARD_SIZE; j++)
      if (stone_compare(j, i, Stone::DOT)) insert_stone(j, i, Stone::SPACE);
}
