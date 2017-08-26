#include "BoardBase.hpp"

class BoardMaster : private BoardBase {
public:
  BoardMaster(const position size = std::make_pair(8, 8));
  BoardMaster(const BoardMaster& src) = default;
  ~BoardMaster() = default;
private:
  const BoardMaster& operator=(const BoardMaster& src);
};

BoardMaster::BoardMaster(const position size)
  : BoardBase(size)
{
}
