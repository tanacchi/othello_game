#include "../include/PlayerSeries.hpp"
#include <chrono>

// ------------------------- Player --------------------------------------------

Player::Player()
  : hand_{BoardSeries::Position{-1, -1}},
    myname_{} 
{
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

void HumanPlayer::set_hand(const BoardSeries::GameBoard& game_board)
{
  std::cout << "Set your hand !!" << std::endl;
  std::string input_str[2];
  for (int i = 0; i < 2; ++i) {
    (!i) ? std::cout << "x" : std::cout << "y";
    std::cout << " = " << std::flush;
    std::cin >> input_str[i];
  }
  int input_num[2];
  for (int i = 0; i < 2; ++i) {
    input_num[i] = std::atoi(input_str[i].c_str());
    if (input_num[i] == 0) throw input_str[i];
  }
  hand_.x = static_cast<BoardSeries::Position::Point>(input_num[0] - 1);
  hand_.y = static_cast<BoardSeries::Position::Point>(input_num[1] - 1);
}

// ------------------------- ComputerPlayer ------------------------------------

ComputerPlayer::ComputerPlayer()
{
  set_myname("Computer");
}

void ComputerPlayer::set_hand(const BoardSeries::GameBoard& game_board)
{
  auto start{std::chrono::system_clock::now()};
  OthelloAI seeker{game_board, 5};
  hand_ = seeker.get_conclusion();
  auto end{std::chrono::system_clock::now()};
  auto msec{std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()};
  std::cout << "time : " << msec << "(millisecond)" << std::endl;
}
