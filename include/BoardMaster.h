#include "BoardBase.h"

class BoardMaster : public BoardBase {
public:
  bool can_continue();
  bool is_available_position(int x, int y);
  int count_reversible_stone(int x, int y);
  int count_stone(Stone target);
  void put_dot_stone();
  void remove_dot_stone();
  void reverse_stone(int x, int y);
};
