struct PlaneVector {
public:
  using Point = unsigned char;
  Point x, y;
  PlaneVector(Point init_x, Point init_y);
  PlaneVector operator+(const PlaneVector& src);
  const PlaneVector& operator+=(const PlaneVector& src);
  const PlaneVector& operator--();
};

PlaneVector::PlaneVector(Point init_x, Point init_y)
  : x{init_x},
    y{init_y}
{
}

PlaneVector PlaneVector::operator+(const PlaneVector& src)
{
  return PlaneVector(x + src.x, y + src.y);
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
