#ifndef BOARD_BASE_H_
#define BOARD_BASE_H_

#include <algorithm>
#include <array>
#include <iostream>
#include <valarray>
#include "Vector2D.hpp"

namespace BoardSeries
{
static const std::array<Vector2D,8ul> direction {
  {{1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}}
};

using Position = Vector2D;
enum class Stone {
  Space,
  White,
  Black,
  Dot
};

class BoardBase {
public:
  BoardBase(const Position& size = Position{8, 8});
  const BoardBase& operator=(const BoardBase& src) = delete;
  virtual ~BoardBase() = default;
  Position::Point width() const;
  Position::Point height() const;
  bool is_inside(Position::Point x, Position::Point y) const;
  bool is_inside(const Position& pos) const;
  Position::Point get_access_num(const Position& pos) const;
  Position::Point get_access_num(Position::Point x, Position::Point y) const;
  void insert(Position::Point x, Position::Point y);
  void insert(Position::Point x, Position::Point y, Stone stone);
  void insert(const Position& pos);
  void insert(const Position& pos, Stone stone);
  BoardSeries::Stone get_enemy_stone() const;
  int get_reversible_length(const Position& pos, const Vector2D& dr) const;
  int count_stone(Stone stone) const;
  bool can_reverse(const Position& pos) const;
  void reverse(const Position& pos);
  bool is_available_position(const Position& pos) const;
  void switch_active_stone();
  friend void show(const BoardBase& src);
protected:
  std::valarray<Stone> board_;
  const Position size_;
  Stone active_stone_;
};
char to_char(Stone stone);
};

#endif // BOARD_BASE_H_
