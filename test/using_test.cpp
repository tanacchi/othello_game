#include <iostream>

using point    = unsigned short;
using position = std::pair<point, point>;

template<typename T>
void show(T src)
{
  std::cout << src << std::endl;
}

void show(position src)
{
  std::cout << "first = "<< src.first << " : second = " << src.second << std::endl;
}

auto main() -> int
{
  show(sizeof(point));
  show(sizeof(int));
  point i = -1;
  show((unsigned int)i);

  position p{65, 66};
  show(p);
  return 0;
}
