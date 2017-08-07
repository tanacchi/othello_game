#include "../include/Player_series.hpp"

// ------------------------- Player --------------------------------------------

void Player::set_mystone(Stone stone)
{
  mystone = stone;
}

Stone Player::get_mystone()
{
  return mystone;
}

void Player::get_hand(int &x, int &y)
{
  x = hand_x;
  y = hand_y;
}

void Player::set_myname(std::string src)
{
  myname = src;
}

std::string Player::get_myname()
{
  return myname;
}

// ------------------------- HumanPlayer ---------------------------------------

HumanPlayer::HumanPlayer()
{
  std::cout << "What is your name ?\n"
            << " > "<< std::flush;
  std::string myname;
  std::getline(std::cin, myname);
  std::cout << std::endl;
  set_myname(myname);
}

bool HumanPlayer::set_hand(const BoardMaster game_board)
{
  std::cout << "Set your hand !!" << std::endl;
  std::string input_str[2];
  for (int i = 0; i < 2; i++) {
    (!i) ? std::cout << "x" : std::cout << "y";
    std::cout << " = " << std::flush;
    std::cin >> input_str[i];
    if (input_str[i] == "revert") return false;
  }
  int input_num[2];
  for (int i = 0; i < 2; i++) input_num[i] = std::atoi(input_str[i].c_str());
  hand_x = input_num[0] - 1;
  hand_y = input_num[1] - 1;
  return true;
}

// ------------------------- ComputerPlayer ------------------------------------

ComputerPlayer::ComputerPlayer()
{
  set_myname("Computer");
}

bool ComputerPlayer::set_hand(const BoardMaster game_board)
{
  OthelloAI* p = new OthelloAI(game_board);
  p->seek(4);
  p->get_conclusion(hand_x, hand_y);
  delete p;
  return true;
}
