#ifndef PLANE_VECTOR_H_
#define PLANE_VECTOR_H_

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

#endif // PLANE_VECTOR_H_
