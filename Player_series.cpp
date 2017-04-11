#include "include/Player_series.h"

// ------------------------- Player --------------------------------------------

void Player::set_my_stone(Stone stone) {
  my_stone = stone;
}

Stone Player::get_my_stone() {
  return my_stone;
}

void Player::get_hand(int &x, int &y) {
  x = hand_x;
  y = hand_y;
}

// ------------------------- HumanPlayer ---------------------------------------

void HumanPlayer::set_hand(const BoardMaster game_board) {
  int input_x, input_y;
  std::cout << "Set your hand !!" << std::endl;
  std::cout << "x = "; std::cin >> input_x;
  std::cout << "y = "; std::cin >> input_y;
  hand_x = input_x - 1; hand_y = input_y - 1;
}

// ------------------------- ComputerPlayer ------------------------------------

void ComputerPlayer::set_hand(const BoardMaster game_board) {
  int dist_x, dist_y;
  OthelloAI* p;
  p = new OthelloAI(game_board, get_my_stone());
  p->seek_effective_hand();
  p->get_conclusion(hand_x, hand_y);
  delete p;
}
