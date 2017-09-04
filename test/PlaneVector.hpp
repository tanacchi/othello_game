#include <iostream>

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

void show(PlaneVector src)
{
  std::cout << &src
            << " : x = " << static_cast<int>(src.x)
            << ", y = " << static_cast<int>(src.y) << std::endl;
}

int main()
{
  PlaneVector va{3, 5};
  PlaneVector vb{2, 5};
  show(va);
  show(vb);
  PlaneVector vc{va+vb};
  show(vc);
  --vc;
  show(vc);
  return 0;
}
