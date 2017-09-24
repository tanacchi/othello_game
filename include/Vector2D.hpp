#ifndef VECTOR_2D_H_
#define VECTOR_2D_H_

struct PlaneVector {
public:
  using Point = char;
  Point x, y;
  PlaneVector(Point init_x, Point init_y);
  PlaneVector operator+(const PlaneVector& src) const;
  PlaneVector operator*(int n) const;
  const PlaneVector& operator+=(const PlaneVector& src);
  const PlaneVector& operator--();
};

#endif // VECTOR_2D_H_
