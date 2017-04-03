#include "include/othello_base.h"
#include "include/Player.h"

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
