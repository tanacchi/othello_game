#include <iostream>
#include <vector>

int global = 0;

class NestClass {
  int num;
  NestClass* sub;
public:
  NestClass(int depth) : num {depth}
  {
    std::cout << "Hello !" << std::endl;
    if (depth > 0) {
      sub = new NestClass[depth-1];
      for (int i=0; i < depth-1; i++) sub[i].init(depth-1);
    }
  }

  NestClass()
  {
    std::cout << "Hello !" << std::endl;
  }
  
  void init(int depth) {
    num = depth;
    if (depth > 0) {
      sub = new NestClass[depth-1];
      for (int i=0; i < depth-1; i++) sub[i].init(depth-1);
    }    
  }
  
  int sum() {
    if (!sub) {
      for (int i = 0; i < num-1; i++) num += sub[i].sum();
    }
    return num;
  }
  
  ~NestClass() {
    if (num > 0) delete[] sub;
    std::cout << "See you " << num << std::endl;;
  }
};

int main() {

  NestClass nest(3);
  std::cout << nest.sum() << std::endl;

  return 0;
}
