#include <iostream>

using point = unsigned short;

template<typename T>
void show(T src)
{
  std::cout << src << std::endl;
}
  
auto main() -> int
{

  show(sizeof(point));
  show(sizeof(unsigned short));
  point i = -1;
  show(i);
  return 0;
}
