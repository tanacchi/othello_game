#include <iostream>
#include <valarray>

int main()
{
  constexpr std::size_t size_x{6}, size_y{6};
  std::valarray<int> data(1, size_x*size_y);
  std::iota(std::begin(data), std::end(data), 1);
  std::for_each(std::begin(data), std::end(data), [](int x){
      std::cout << x << ' ' << std::flush;
    });
  std::cout << std::endl;

  std::valarray<std::size_t> mask = {11, 10, 17, 16};
  std::indirect_array<int> ind = data[mask];

  ind  = -1;
  //  ind *= std::valarray<int>(2, mask.size()); 
  // std::for_each(std::begin(data), std::end(data), [](int x){
  //     std::cout << x << ' ' << std::flush;
  //   });
  // std::cout << std::endl;

  // std::slice_array<int> slice = data[std::slice(4, 5, 2)];
  // slice = 0;
  std::size_t start = 6;
  std::valarray<std::size_t> length = {2, 3};
  std::valarray<std::size_t> stride = {2, size_x};

  //  std::gslice_array<int> gslice = data[std::gslice(start, length, stride)];

  data[std::gslice(start, length, stride)] = 0;
  std::cout << "Hey" << std::endl;  

  for (int i = 0; i < size_y; std::cout.put('\n'), i++) {
    std::gslice_array<int> sliced = data[std::slice(size_x*i, size_x, 1)];
    for (auto x : sliced)
      std::cout << x << '\t' << std::flush;
  }
  std::cout << std::endl;
  
  return 0;
}
