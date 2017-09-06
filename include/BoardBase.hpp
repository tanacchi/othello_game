#ifndef BOARD_BASE_H_
#define BOARD_BASE_H_

#include <algorithm>
#include <vector>
#include <valarray>
#include "PlaneVector.hpp"

#include <functional>

static const std::array<PlaneVector,8ul> direction {{
    {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}
  }};

class BoardBase {
public:
  using Position = PlaneVector;
  enum class Stone {
    Space,
    White,
    Black,
    Dot
  };
  BoardBase(const Position& size = Position{8, 8});
  const BoardBase& operator=(const BoardBase& src) = delete;
  virtual ~BoardBase() = default;
  PlaneVector::Point width() const;
  PlaneVector::Point height() const;
  bool is_inside(PlaneVector::Point x, PlaneVector::Point y) const;
  bool is_inside(const Position& pos) const;
  PlaneVector::Point get_access_num(const Position& pos) const;
  PlaneVector::Point get_access_num(PlaneVector::Point x, PlaneVector::Point y) const;
  void insert(PlaneVector::Point x, PlaneVector::Point y);
  void insert(PlaneVector::Point x, PlaneVector::Point y, Stone&& stone);
  void insert(const Position& pos);
  BoardBase::Stone get_enemy_stone() const;
  int get_reversible_length(Position pos, PlaneVector dr) const;
  int count_stone(BoardBase::Stone stone) const;
  bool can_reverse(const Position& pos) const;
  void reverse(Position pos);
  bool is_available_position(const Position& pos) const;
  void switch_active_stone();
protected:
  std::valarray<Stone> board_;
  const Position size_;
  Stone active_stone_;
private:
};

#endif // BOARD_BASE_H_
