#include <iostream>
#include <vector>

class NestClass {
  int num;
  int array[10];
  NestClass* sub;
public:
  NestClass(int dept) {
    num = dept;
    for (int i = 0; i < 10; i++) array[i] = num;
    std::cout << "Hello !!" << dept << std::endl;
    if (dept > 0) sub = new NestClass[5] { dept-1, dept-1, dept-1, dept-1, dept-1 };
  }
  int sum() {
    if (array[0] > 0)
      for (int i = 0; i < 5; i++) num += (sub+i)->sum();
    for (int i = 0; i < 10; i++) num += array[i];
    return num;
  }
  ~NestClass() {
    delete[] sub;
    std::cout << "See you~~" << num << std::endl;
  }
};

int main() {

  NestClass nest(5);
  std::cout << nest.sum() << std::endl;

  return 0;
}
