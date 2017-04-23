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
      // sub = new NestClass[d-1];
      // for (int i=0; i < d-1; i++) sub[i].init(d-1);
    }
  }

  NestClass() : num{-1}, d{-1}
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

  void show() {
    std::cout << num << std::endl;
  }
  
  ~NestClass() {
    std::cout << "See you " << d << std::endl;;
  }

  NestClass& operator=(NestClass& src) {
    num = src.num;
    d = src.d;
  }
};

int main() {

  NestClass nest(4);
  NestClass second;

  nest.show();
  second = nest;
  second.show();
  
  //  std::cout << nest.sum() << std::endl;

  return 0;
}
