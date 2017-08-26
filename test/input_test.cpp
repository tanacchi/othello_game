#include <iostream>

int main()
{
  std::string ss;
  std::cout << "> " << std::flush;
  std::cin >> ss;

  unsigned char num = std::atoi(ss.c_str());
  std::cout << num << std::endl;

  if (num == 65) std::cout << "65!!" << std::endl;
  return 0;
}
