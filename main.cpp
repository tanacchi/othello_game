#include "include/Player_series.h"

enum class Mode {
  NORMAL_F,
  NORMAL_B,
  PERSONAL,
  AUTO
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
  ASK,
  ED
};

/*

TODO : プレイヤー管理の方法を検討
TODO : パスされたときの後処理

REFACT : 入力部分を設計しなおしてみる
REFACT : 高度な出力を使ってみる

*/

/*

AI と他のクラスの関係とか整理
x
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

[設定可能にする項目]
--personal human vs human
--normal   human vs cpu    --level  cpu's level
--auto     cpu   vs cpu    --level  cpu's level

*/

class HandList {
  int turn;
  Stone stone;
  int hand_x;
  int hand_y;
public:
  HandList(int t, Stone s, int x, int y);
  void report();
};

HandList::HandList(int t, Stone s, int x, int y) {
    turn = t; stone = s; hand_x = x; hand_y = y;
}

void HandList::report() {
  std::cout << "[turn] : " << turn << '\t';
  std::cout << "Stone : " << convert_stone_to_char(stone) << '\t';
  std::cout << "x = " << hand_x << ", y = " << hand_y << std::endl;;
}

class GameMaster {
  BoardMaster board;
  Player *participant[2];
  Player *active_player;
  int turn;
  int x, y;
  std::list<HandList> hand_list;
public:
  GameMaster(Player* player[]);
  Task run(Task mode);
  Task task_init();
  Task task_op();
  Task task_set();
  Task task_insert();
  Task task_write();
  Task task_judge();
  Task task_switch();
  Task task_ask();
  Task task_ed();
  void show_hand_list();
};

GameMaster::GameMaster(Player* player[]) {
  participant[0] = player[0];
  participant[1] = player[1];
  participant[0]->set_my_stone(Stone::WHITE);
  participant[1]->set_my_stone(Stone::BLACK);
}

Task GameMaster::run(Task mode) {
  switch (mode) {
  case Task::INIT:   return task_init();
  case Task::OP:     return task_op();
  case Task::SET:    return task_set();
  case Task::INSERT: return task_insert();
  case Task::WRITE:  return task_write();
  case Task::JUDGE:  return task_judge();
  case Task::SWITCH: return task_switch();
  case Task::ASK:    return task_ask();
  case Task::ED:     return task_ed();
  }
}

Task GameMaster::task_init() {
  turn = 0;
  board.init_board();
  active_player = participant[0];
  return Task::OP;
}

Task GameMaster::task_op() {
  Stone active_stone = active_player->get_my_stone();
  board.set_active_stone(active_stone);
  std::cout << "turn " << turn + 1 << std::endl;
  std::cout << "WHITE STONE (" << convert_stone_to_char(Stone::WHITE) << ") : " << board.count_stone(Stone::WHITE) << '\n'
            << "BLACK STONE (" << convert_stone_to_char(Stone::BLACK) << ") : " << board.count_stone(Stone::BLACK) << '\n' <<std::endl;
  std::cout << "Now is " << convert_stone_to_char(active_player->get_my_stone()) << std::endl;
  board.put_dot_stone();
  board.show_board();
  return Task::SET;
}

Task GameMaster::task_set() {
  if (!board.count_stone(Stone::DOT)) { std::cout << "PASS !!!" << std::endl; return Task::JUDGE; }
  active_player->set_hand(board);
  active_player->get_hand(x, y);
  if (board.is_available_position(x, y)) return Task::INSERT;
  else { std::cout << "It's wrong hand !! Try again." << std::endl; return Task::SET; }
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
  return (board.can_continue()) ? Task::SWITCH : Task::ASK;
}

Task GameMaster::task_switch() {
  active_player = participant[++turn % 2];
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  return Task::OP;
}

Task GameMaster::task_ask() {
  std::cout << "WHITE STONE (" << convert_stone_to_char(Stone::WHITE) << ") : " << board.count_stone(Stone::WHITE) << '\n'
            << "BLACK STONE (" << convert_stone_to_char(Stone::BLACK) << ") : " << board.count_stone(Stone::BLACK) << '\n' <<std::endl;
  show_hand_list();
  std::string answer;
  std::cout << "Continue ?? (yes/no)\n>"; 
  std::cin >> answer;
  if (answer == "yes") return Task::INIT;
  else if (answer == "no") return Task::ED;
  else return Task::ASK;
}

Task GameMaster::task_ed() {
  return Task::ED;
}

void GameMaster::show_hand_list() {
  std::list<HandList>::iterator p {hand_list.begin()};
  while(p != hand_list.end()) {
    p++->report();
  }
}

void show_usage() {
  std::cout << '\n'
            << "***************************************************************************************\n"
            << "* [Usage]                                                                             *\n"
            << "* Options  : --normal <first player (human or cpu)>（通常のコンピューターとの対戦）   *\n"
            << "*            --personal（２人での対人戦）                                             *\n" 
            << "*            --auto（コンピューター同士での自動プレイ）                               *\n"
            << "***************************************************************************************\n" << std::endl;
}

int main(int argc, char ** argv) {

  Player* player[2];

  player[0] = new ComputerPlayer;
  player[1] = new ComputerPlayer;
  
  Task task {Task::INIT};
  GameMaster master(player);
  while (task != Task::ED) task = master.run(task);
  std::cout << "See you~~\n";
  return 0;
}
