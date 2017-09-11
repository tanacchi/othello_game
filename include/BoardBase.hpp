#ifndef BOARD_BASE_H_
#define BOARD_BASE_H_

#include <algorithm>
#include <iostream>
#include <vector>
#include <valarray>

#include <functional>

struct PlaneVector {
public:
  using Point = char;
  Point x, y;
  PlaneVector(Point init_x, Point init_y);
  PlaneVector operator+(const PlaneVector& src);
  PlaneVector operator*(int n);
  const PlaneVector& operator+=(const PlaneVector& src);
  const PlaneVector& operator--();
};

namespace BoardSeries
{
static const std::array<PlaneVector,8ul> direction {
  {{1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}}
};

using Position = PlaneVector;
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
  int get_reversible_length(Position pos, PlaneVector dr) const;
  int count_stone(Stone stone) const;
  bool can_reverse(const Position& pos) const;
  void reverse(Position pos);
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
