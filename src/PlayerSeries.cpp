#include "../include/Player_series.hpp"

// ------------------------- Player --------------------------------------------

Player::Player(BoardSeries::Stone mystone)
  : mystone_ {mystone},
    myname_(),
    hand_{BoardSeries::Position{-1, -1}}
{
}

BoardSeries::Stone Player::get_mystone() const
{
  return mystone_;
}

BoardSeries::Position Player::get_hand() const
{
  return hand_;
}

void Player::set_myname(std::string src)
{
  myname_ = src;
}

std::string Player::get_myname() const
{
  return myname_;
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

bool HumanPlayer::set_hand(const GameBoard& game_board)
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
  hand_.x = static_cast<Position::Point>(input_num[0] - 1);
  hand_.y = static_cast<Position::Point>(input_num[1] - 1);
  return true;
}

// ------------------------- ComputerPlayer ------------------------------------

ComputerPlayer::ComputerPlayer()
{
  set_myname("Computer");
}

bool ComputerPlayer::set_hand(const GameBoard& game_board)
{
  // OthelloAI* p = new OthelloAI(game_board);
  // p->seek(4);
  // // p->get_conclusion(hand_x_, hand_y_);
  // delete p;
  return true;
}
