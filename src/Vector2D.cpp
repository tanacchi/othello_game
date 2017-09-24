#include "../include/Vector2D.hpp"

PlaneVector::PlaneVector(Point init_x, Point init_y)
  : x{init_x},
    y{init_y}
{
}

PlaneVector PlaneVector::operator+(const PlaneVector& src) const
{
  return PlaneVector(x + src.x, y + src.y);
}

PlaneVector PlaneVector::operator*(int n) const
{
  return PlaneVector(x * n, y * n);
}

const PlaneVector& PlaneVector::operator+=(const PlaneVector& src)
{
  x += src.x; y += src.y;
  return *this;
}

const PlaneVector& PlaneVector::operator--()
{
  --x; --y;
  return *this;
}

