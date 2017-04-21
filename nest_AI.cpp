#include <iostream>
#include <vector>

int global = 0;

class NestClass {
  int num;
  int d;
  NestClass* sub;
public:
  NestClass(int depth) : num {depth}, d{depth}
  {
    std::cout << "Hello !" << std::endl;
    if (d > 0) {
      sub = new NestClass[d-1];
      for (int i=0; i < d-1; i++) sub[i].init(d-1);
    }
  }

  NestClass()
  {
    std::cout << "Hello !" << std::endl;
  }
  
  void init(int depth) {
    num = d = depth;
    if (d > 0) {
      sub = new NestClass[d-1];
      for (int i = 0; i < d - 1; i++) sub[i].init(d-1);
    }
  }
  
  int sum() {
    if (sub) {
      for (int i = 0; i < d-1; i++) num += sub[i].sum();
    }
    if (d> 0) delete[] sub;
    return num;
  }
  
  ~NestClass() {
    std::cout << "See you " << d << std::endl;;
  }
};

int main() {

  NestClass nest(4);
  std::cout << nest.sum() << std::endl;

  return 0;
}
