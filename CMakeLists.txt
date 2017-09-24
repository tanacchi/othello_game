cmake_minimum_required(VERSION 3.5.1)

add_definitions("-Wall --std=c++14")
include_directories(include)
add_executable(othello_game.out
  src/main.cpp
  src/AiBoard.cpp
  src/BoardBase.cpp
  src/GameBoard.cpp
  src/GameMaster.cpp
  src/OthelloAI.cpp
  src/PlayerSeries.cpp
  src/Vector2D.cpp
)
