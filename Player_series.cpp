#include "include/Player_series.h"

// ------------------------- Player --------------------------------------------

void Player::set_mystone(Stone stone) {
  mystone = stone;
}

Stone Player::get_mystone() {
  return mystone;
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
  p = new OthelloAI(game_board, get_mystone());
  p->seek();
  p->get_conclusion(hand_x, hand_y);
  delete p;
}
