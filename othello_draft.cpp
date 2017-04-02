#include <chrono>
#include <iostream>
#include <list>
#include <random>
#include <thread>
#include <vector>

#define BOARD_SIZE 8

enum class Stone {
  WHITE,
  BLACK,
  SPACE,
  DOT
};

enum class Task {
  INIT,
  OP,
  SHOW,
  SET,
  INSERT,  
  WRITE,
  JUDGE,
  SWITCH,
  ED
};

const int dx[8] = { 0, 1, 1, 1, 0,-1,-1,-1 };
const int dy[8] = {-1,-1, 0, 1, 1, 1, 0,-1 };

/*

TODO : プレイヤー管理の方法を検討
TODO : パスされたときの後処理

REFACT : 入力部分を設計しなおしてみる
REFACT : 高度な出力を使ってみる

*/

/*

AI と他のクラスの関係とか整理

[AIのしごと]
仮想のボードを用意する
仮想ボードをMasterから同期する
自分でDotを配置する
Dotの座標とスコアを格納するリストを用意
メンバ関数でDotごとに評価をつける
はじめはリバースできる石の個数で採点
次に角の評価点を上げる
また自らの評価でenemy_stoneを置き
5手ぐらい先まですすめる
最終的に評価点（の得失点差）が一番高い座標を返す
各段階で評価してからの
最終的な評価を合計する感じで
先読みの際にenemy_stoneの置き方をどうしようかって感じではある
また図でもかきながら考えてみよう

[AIが必要とするもの]
評価回数管理 <- private
評価関数
｛ポジションによる評価
裏返す個数による評価｝
enemy_stoneを選んで置く操作
評価を回数分実行するやつ

*/

/*

put_dot_stone

x, yを格納

「Dot ごとに評価」

？？enemyの設定がゲロむず

最も評価の高いやつを選択して返す

*/

class BoardBase {
  std::vector<std::vector<Stone> > board;
  Stone active_stone;
public:
  BoardBase();
  Stone get_enemy();
  bool stone_compare(int x, int y, Stone src);
  inline bool is_inside_board(int x, int y);
  int count_stone(Stone target);
  int get_reversible_length(int x, int y, int dx, int dy);
  void init_board();
  void insert_stone(int x, int y); 
  void insert_stone(int x, int y, Stone stone); 
  void set_active_stone(Stone stone);
  void show_board();
  Stone get_stone(int x, int y);
};

BoardBase::BoardBase() {
  board = std::vector<std::vector<Stone> >(BOARD_SIZE, std::vector<Stone>(BOARD_SIZE));
}

void BoardBase::init_board() {
  for (int i = 0; i < board.size(); i++)
    for (int j = 0; j < board.front().size(); j++)
      board[i][j] = Stone::SPACE;
  board[3][3] = board[4][4] = Stone::WHITE;
  board[3][4] = board[4][3] = Stone::BLACK;
}

Stone BoardBase::get_stone(int x, int y) {
  return board[y][x];
}

char convert_stone_to_char(Stone src) {
  switch (src) {
  case Stone::SPACE: return ' ';
  case Stone::BLACK: return 'X';
  case Stone::WHITE: return 'O';
  case Stone::DOT:   return '*';
  }
}

void BoardBase::show_board() {
  std::cout << "---------------------------" << std::endl;
  std::cout << "  ";
  for (int i = 0; i < BOARD_SIZE; i++) std::cout << i+1 << ' ';
  std::cout << std::endl;
  for (int i = 0; i < BOARD_SIZE; i++) {
    std::cout << i+1 << ' ';
    for (int j = 0; j < BOARD_SIZE; j++) std::cout << convert_stone_to_char(board[i][j]) << ' ';
    std::cout << std::endl;
  }
  std::cout << "---------------------------" << std::endl;
}

void BoardBase::set_active_stone(Stone stone) {
  active_stone = stone;
}

void BoardBase::insert_stone(int x, int y) {
  board[y][x] = active_stone;
}

void BoardBase::insert_stone(int x, int y, Stone stone) {
  board[y][x] = stone;
}

bool BoardBase::stone_compare(int x, int y, Stone src) {
  return board[y][x] == src;
}

int BoardBase::get_reversible_length(int x, int y, int dx, int dy) {
  Stone enemy_stone = get_enemy(); 
  for (int i = 1; is_inside_board(x + i*dx, y + i*dy); i++) {
    Stone target = board[y + i*dy][x + i*dx];
    if (target == active_stone) return i-1;
    else if (target == enemy_stone) continue;
    else break;
  }
  return 0;
}

inline bool BoardBase::is_inside_board(int x, int y) {
  return (0 <= x && x <= BOARD_SIZE) && (0 <= y && y < BOARD_SIZE);
}

Stone BoardBase::get_enemy() {
  return (active_stone == Stone::WHITE) ? Stone::BLACK : Stone::WHITE;
}

class BoardMaster : public BoardBase {
public:
  inline bool can_continue();
  inline bool is_available_position(int x, int y);
  int count_reversible_stone(int x, int y);
  int count_stone(Stone target);
  void put_dot_stone();
  void remove_dot_stone();
  void reverse_stone(int x, int y);
};

bool BoardMaster::is_available_position(int x, int y) {
  return is_inside_board(x, y) && stone_compare(x, y, Stone::SPACE) && count_reversible_stone(x, y);
}

inline bool BoardMaster::can_continue() {
  return count_stone(Stone::SPACE) && count_stone(Stone::BLACK) && count_stone(Stone::WHITE);
}

int BoardMaster::count_stone(Stone target) {
  int count = 0;
  for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
      if (stone_compare(j, i, target)) count++;
  return count;
}

int BoardMaster::count_reversible_stone(int x, int y) {
  int reversible_stone_count = 0;
  for (int i = 0; i < 8; i++) reversible_stone_count += get_reversible_length(x, y, dx[i], dy[i]);
  return reversible_stone_count;
}

void BoardMaster::reverse_stone(int x, int y) {
  int reverse_length = 0;
  for (int i = 0; i < 8; i++) {
    reverse_length = get_reversible_length(x, y, dx[i], dy[i]);
    for (int j = 1; j <= reverse_length; j++) insert_stone(x + j*dx[i], y + j*dy[i]);
  }
}

void BoardMaster::put_dot_stone() {
  for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
      if (is_available_position(j, i)) insert_stone(j, i, Stone::DOT);
}

void BoardMaster::remove_dot_stone() {
  for (int i = 0; i< BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
      if (stone_compare(j, i, Stone::DOT)) insert_stone(j, i, Stone::SPACE);
}

class Player {
  Stone my_stone;
  int hand_x, hand_y;
public:
  void set_my_stone(Stone stone);
  void input_position(const int input_x, const int input_y);
  virtual void set_hand();
  Stone get_my_stone();
  void get_hand(int &x, int &y);
};

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

class HumanPlayer : public Player {
public:
  void set_hand();
};

void HumanPlayer::set_hand() {
  int input_x, input_y;
  std::cout << "First, input 'x' !! \n> "; std::cin >> input_x;
  std::cout << "Next, input 'y' !! \n> ";  std::cin >> input_y;
  input_position(input_x - 1, input_y - 1);
}

class StoneScoreList {
  int x;
  int y;
  std::vector<int> score;
  int total_score;
public:
  void set_total_score() {
    for (int i = 0; i < score.size(); i++) total_score += score[i];
  }
};

class OthelloAI : private BoardMaster {
  int dist_x, dist_y;
  std::mt19937 rand_pos;
  std::vector<StoneScoreList> score_list;
public:
  OthelloAI();
  void get_current_board(BoardMaster game_board);
  void get_conclusion(int &x, int &y);
  void random_maker();
};

void OthelloAI::get_conclusion(int &x, int &y) { 
  x = dist_x;
  y = dist_y;
}

OthelloAI::OthelloAI() : rand_pos { std::random_device{}() }
{
}

void OthelloAI::random_maker() {
  std::uniform_int_distribution<int> rand100(0, 7);
  dist_x = rand100(rand_pos);
  dist_y = rand100(rand_pos);
}

void OthelloAI::get_current_board(BoardMaster game_board) {
  for (int i = 0; i < BOARD_SIZE; i++)
    for (int j = 0; j < BOARD_SIZE; j++)
      insert_stone(j, i, game_board.get_stone(j, i));
}

class ComputerPlayer : public Player, private OthelloAI {
public:
  void set_hand();
};

void ComputerPlayer::set_hand() {
  int dist_x, dist_y;
  random_maker();  //  !!!!!!!!!!!!!!!!!!!!
  get_conclusion(dist_x, dist_y);
  input_position(dist_x, dist_y);
}

class HandList {
  int turn;
  Stone stone;
  int hand_x;
  int hand_y;
public:
  HandList(int t, Stone s, int x, int y) {
    turn = t; stone = s; hand_x = x; hand_y = y;
  }
  void report() {
    std::cout << "[turn] : " << turn << ' ';
    std::cout << "Stone : " << convert_stone_to_char(stone) << ' ';
    std::cout << "x = " << hand_x << ", y = " << hand_y << std::endl;
  }
};

class GameMaster {
  BoardMaster board;
  ComputerPlayer cpu[2];
  Player* active_player;
  int turn;
  int x, y;
  std::list<HandList> hand_list;
public:
  Task run(Task mode);
  Task task_init();
  Task task_op();
  Task task_set();
  Task task_insert();
  Task task_write();
  Task task_judge();
  Task task_switch();
  Task task_ed();
  void show_hand_list();
};

Task GameMaster::run(Task mode) {
  switch (mode) {
  case Task::INIT:   return task_init();
  case Task::OP:     return task_op();
  case Task::SET:    return task_set();
  case Task::INSERT: return task_insert();
  case Task::WRITE:  return task_write();
  case Task::JUDGE:  return task_judge();
  case Task::SWITCH: return task_switch();
  case Task::ED:     return task_ed();
  }
}

Task GameMaster::task_init() {
  turn = 0;
  board.init_board();
  cpu[0].set_my_stone(Stone::WHITE);
  cpu[1].set_my_stone(Stone::BLACK);
  active_player = &cpu[0];
  return Task::OP;
}

Task GameMaster::task_op() {
  board.set_active_stone(active_player->get_my_stone());
  std::cout << "turn " << turn + 1 << std::endl;
  std::cout << "Now is " << convert_stone_to_char(active_player->get_my_stone()) << std::endl;
  board.put_dot_stone();
  board.show_board();
  return Task::SET;
}

Task GameMaster::task_set() {
  active_player->set_hand();
  active_player->get_hand(x, y);
  if (!board.count_stone(Stone::DOT)) { std::cout << "PASS !!!" << std::endl; return Task::JUDGE; }
  if (board.stone_compare(x, y, Stone::DOT)) return Task::INSERT;
  else return Task::SET;
}

Task GameMaster::task_insert() {
  board.insert_stone(x, y);
  board.reverse_stone(x, y);
  return Task::WRITE;
}

Task GameMaster::task_write() {
  hand_list.push_back(HandList(turn+1, active_player->get_my_stone(), x+1, y+1));
  return Task::JUDGE;
}

Task GameMaster::task_judge() {
  board.remove_dot_stone();
  board.show_board();
  std::cout << "\n\n" << std::endl;
  return (board.can_continue()) ? Task::SWITCH : Task::ED;
}

Task GameMaster::task_switch() {
  active_player = &cpu[++turn % 2];
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  return Task::OP;
}

Task GameMaster::task_ed() {
  std::cout << "BLACK STONE : " << board.count_stone(Stone::BLACK) << '\n'
            << "WHITE STONE : " << board.count_stone(Stone::WHITE) << std::endl;
  show_hand_list();
  exit (0);
}

void GameMaster::show_hand_list() {
  std::list<HandList>::iterator p = hand_list.begin();
  while(p != hand_list.end()) {
    p++->report();
  }
}

int main() {
  Task mode = Task::INIT;
  GameMaster master;

  while (1)
    mode = master.run(mode);

  return 0;
}


