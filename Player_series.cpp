#include "include/Player_series.h"

// ------------------------- Player --------------------------------------------

void Player::set_my_stone(Stone stone) {
  my_stone = stone;
}

void Player::set_hand(BoardMaster game_board) {
}

Stone Player::get_my_stone() {
  return my_stone;
}

void Player::get_hand(int &x, int &y) {
  x = hand_x;
  y = hand_y;
}

// ------------------------- HumanPlayer ---------------------------------------

void HumanPlayer::set_hand(BoardMaster game_board) {
  std::cout << "Set your hand !!" << std::endl;
  std::cout << "x = "; std::cin >> hand_x;
  std::cout << "y = "; std::cin >> hand_y;
}

// ------------------------- ComputerPlayer ------------------------------------

void ComputerPlayer::set_hand(BoardMaster game_board) {
  int dist_x, dist_y;
  OthelloAI* p;
  p = new OthelloAI(game_board, get_my_stone());
  p->seek_effective_hand();
  p->get_conclusion(hand_x, hand_y);
  delete p;
}
