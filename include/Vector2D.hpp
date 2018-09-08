#ifndef VECTOR_2D_H_
#define VECTOR_2D_H_

#include <cstdint>

struct Vector2D {
public:
  using Point = std::int_fast8_t;
  Point x, y;
  Vector2D(Point init_x, Point init_y);
  Vector2D operator+(const Vector2D& src) const;
  Vector2D operator*(int n) const;
  const Vector2D& operator+=(const Vector2D& src);
  const Vector2D& operator--();
};

#endif // VECTOR_2D_H_
