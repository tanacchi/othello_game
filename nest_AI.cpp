#include <iostream>
#include <vector>

int global = 0;

class NestClass {
  int num;
  int serial_num;
  std::vector <NestClass> sub;
public:
  NestClass(int dept) {
    num = 1;
    serial_num = global++;
    std::cout << "Hello ! " << serial_num << std::endl;
    for (int i = 0; i < dept-1; i++) sub.push_back(NestClass(dept-1));
  }
  int sum() {
    if (!sub.empty()) {
      for (int i = 0; i < sub.size(); i++) num += sub[i].sum();
      std::cout << "Hi " << serial_num << std::endl;  
    }
    return num;
  }
  ~NestClass() {
    std::cout << "See you " << serial_num << std::endl;;
  }
};

int main() {

  NestClass nest(3);
  std::cout << nest.sum() << std::endl;

  return 0;
}
