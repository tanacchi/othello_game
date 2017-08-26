#include <iostream>
#include <functional>

int main()
{

  std::size_t width = 3, height = 5;;
  std::pair<size_t&, size_t&> a = std::make_pair(std::ref(width), std::ref(height));

  std::cout << a.first << ' ' << a.second << std::endl;

  a.first++; a.second++;
  
  std::cout << width << ' ' << height << std::endl;
  
  return 0;
}
