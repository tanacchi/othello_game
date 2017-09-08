#ifndef BOARD_MASTER_H_
#define BOARD_MASTER_H_

#include "othello_base.hpp"

class BoardMaster {
public:
  BoardMaster();
  BoardMaster(const BoardMaster& src);
  const BoardMaster& operator=(BoardMaster& src);
  ~BoardMaster() = default;
  Stone get_enemy() const;
  void switch_active_stone();
  bool is_inside_board(int x, int y) const;
  unsigned int get_reversible_length(int x, int y, int dx, int dy) const;
  int count_stone(Stone target) const;
  void init();
  void insert(int x, int y); 
  void insert(int x, int y, Stone stone); 
  void set_active_stone(Stone stone);
  bool can_continue() const;
  bool is_available_position(int x, int y) const;
  int count_reversible_stone(int x, int y) const;
  void put_dot_stone();
  void remove_dot_stone();
  void reverse_stone(int x, int y);
  void show() const;
  double get_status_score() const;
private:
  std::vector<std::vector<Stone> > board_;
  Stone active_stone_;
};

char to_char(Stone src);

#endif // BOARD_MASTER_H_
