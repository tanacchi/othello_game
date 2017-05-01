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

void Player::set_myname(std::string src) {
  myname = src;
}

std::string Player::get_myname() {
  return myname;
}

// ------------------------- HumanPlayer ---------------------------------------

HumanPlayer::HumanPlayer() {
  std::string myname;
  std::cout << "What is your name ?\n"
            << " > "<< std::flush;
  std::getline(std::cin, myname);
  std::cout << std::endl;
  set_myname(myname);
}

void HumanPlayer::set_hand(const BoardMaster game_board) {
  int input_x, input_y;
  std::cout << "Set your hand !!" << std::endl;;
  std::cout << "x = " << std::flush; std::cin >> input_x;
  std::cout << "y = " << std::flush; std::cin >> input_y; 
  hand_x = input_x - 1; hand_y = input_y - 1;
}

// ------------------------- ComputerPlayer ------------------------------------

ComputerPlayer::ComputerPlayer() {
  set_myname("Computer");
}

void ComputerPlayer::set_hand(const BoardMaster game_board) {
  OthelloAI* p = new OthelloAI(game_board);
  p->seek(4);
  p->get_conclusion(hand_x, hand_y);
  delete p;
}
