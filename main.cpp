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

Player型ポインタで扱いたいので
set_handは仮想関数で書きたい
* フレンド関数とやらを試してみる
* そもそものPlayer系統、BoardMaster系統、OthelloAI系統の関係や設計を見なおしてみる

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
  std::cout << "x = " << hand_x << ", y = " << hand_y << std::endl;
}

class GameMaster {
  BoardMaster board;
  HumanPlayer human[2];
  ComputerPlayer cpu[2];
  Player *participant[2];
  Player *active_player;
  int turn;
  int x, y;
  std::list<HandList> hand_list;
public:
  GameMaster(Mode mode);
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

GameMaster::GameMaster(Mode mode) {
  switch (mode) {
  case Mode::NORMAL_F:
    participant[0] = &human[0];
    participant[1] = &cpu[0];
    break;
  case Mode::NORMAL_B:
    participant[0] = &cpu[0];
    participant[1] = &human[0];
    break;
  case Mode::PERSONAL:
    participant[0] = &human[0];
    participant[1] = &human[1];
    break;
  case Mode::AUTO:
    participant[0] = &cpu[0];
    participant[1] = &cpu[1];
    break;
  }
  participant[0]->set_my_stone(Stone::WHITE);
  participant[1]->set_my_stone(Stone::BLACK);
}

Task GameMaster::run(Task mode) {
  switch (mode) {  case Task::INIT:   return task_init();
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
  active_player = participant[0];
  return Task::OP;
}

Task GameMaster::task_op() {
  Stone active_stone = active_player->get_my_stone();
  board.set_active_stone(active_stone);
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
  active_player = participant[++turn % 2];
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

void show_usage() {
  std::cout << "[Usage] \n"
            << "Options  : --normal <first player (human or cpu)>（通常のコンピューターとの対戦）\n"
            << "           --personal（２人での対人戦）\n"
            << "           --auto（コンピューター同士での自動プレイ）" << std::endl;
}

int main(int argc, char ** argv) {
  
  Mode mode = Mode::NORMAL_F;
  if (argc > 1) {
    if (!strcmp(argv[1], "--normal")) 
      if (argc > 2) {
        if (!strcmp(argv[2], "human")) mode = Mode::NORMAL_F;
        else if (!strcmp(argv[2], "cpu")) mode = Mode::NORMAL_B;
        else show_usage();
      }
    else if (!strcmp(argv[1], "--personal")) mode = Mode::PERSONAL;
    else if (!strcmp(argv[1], "--auto"))     mode = Mode::AUTO;
    else show_usage();
  }
  
  Task task = Task::INIT;
  GameMaster master(mode);
  while (1) task = master.run(task);

}
