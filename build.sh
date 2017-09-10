# g++ -c --std=c++14 src/*.cpp -Wall
# g++ --std=c++14 *.o -Wall -o othello_game.out
# rm *.o

g++ -c --std=c++14 src/AiBoard.cpp src/BoardBase.cpp src/GameBoard.cpp src/GameMaster.cpp src/PlaneVector.cpp src/PlayerSeries.cpp src/main.cpp
g++ --std=c++14 *.o -Wall -o othello_game.out
rm *.o
