#include "othello_base.h"

class BoardBase {
  std::vector<std::vector<Stone> > board;
  Stone active_stone;
public:
  BoardBase();
  Stone get_enemy();
  bool stone_compare(int x, int y, Stone src);
  bool is_inside_board(int x, int y);
  int count_stone(Stone target);
  int get_reversible_length(int x, int y, int dx, int dy);
  void init_board();
  void insert_stone(int x, int y); 
  void insert_stone(int x, int y, Stone stone); 
  void set_active_stone(Stone stone);
  void show_board();
  Stone get_stone(int x, int y);
};

char convert_stone_to_char(Stone src);
