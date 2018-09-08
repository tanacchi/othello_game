#include "../include/Vector2D.hpp"

Vector2D::Vector2D(Point init_x, Point init_y)
  : x{init_x},
    y{init_y}
{
}

Vector2D Vector2D::operator+(const Vector2D& src) const
{
  return Vector2D(x + src.x, y + src.y);
}

Vector2D Vector2D::operator*(int n) const
{
  return Vector2D(x * n, y * n);
}

const Vector2D& Vector2D::operator+=(const Vector2D& src)
{
  x += src.x; y += src.y;
  return *this;
}

const Vector2D& Vector2D::operator--()
{
  --x; --y;
  return *this;
}

