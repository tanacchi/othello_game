#include "include/Player_series.h"

void Player::set_my_stone(Stone stone) {
  my_stone = stone;
}

void Player::input_position(const int input_x, const int input_y) {
  hand_x = input_x;
  hand_y = input_y;
}

void Player::set_hand()
{
}

Stone Player::get_my_stone() {
  return my_stone;
}

void Player::get_hand(int &x, int &y) {
  x = hand_x;
  y = hand_y;
}

void HumanPlayer::set_hand() {
  int input_x, input_y;
  std::cout << "Set your hand !!" << std::endl;
  std::cout << "x = "; std::cin >> input_x;
  std::cout << "y = "; std::cin >> input_y;
  input_position(input_x - 1, input_y - 1);
}

void ComputerPlayer::set_hand() {
  int dist_x, dist_y;
  random_maker();
  seek_effective_hand();
  get_conclusion(dist_x, dist_y);
  input_position(dist_x, dist_y);
}
