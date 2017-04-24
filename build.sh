#g++ -c --std=c++14 *.cpp
g++ --std=c++14 main.cpp BoardMaster.cpp Player_series.cpp OthelloAI.cpp -c
g++ --std=c++14 *.o
rm *.o
