#include "othello_base.h"

class BoardMaster {
  std::vector<std::vector<Stone> > board;
  Stone active_stone;
public:
  BoardMaster();
  ~BoardMaster();
  Stone get_enemy();
  void switch_active_stone();
  bool is_inside_board(int x, int y);
  int get_reversible_length(int x, int y, int dx, int dy);
  int count_stone(Stone target);
  void init();
  void insert(int x, int y); 
  void insert(int x, int y, Stone stone); 
  void set_active_stone(Stone stone);
  Stone get_stone(int x, int y);
  bool can_continue();
  bool is_available_position(int x, int y);
  int count_reversible_stone(int x, int y);
  void put_dot_stone();
  void remove_dot_stone();
  void reverse_stone(int x, int y);
  void show();
  BoardMaster& operator=(BoardMaster& src);
};

char convert_stone_to_char(Stone src);
