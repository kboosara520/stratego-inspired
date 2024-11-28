#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <vector>

class Observer {
 public:
  virtual void displayBoard(int turn, const std::vector<std::pair<int, int>> &changes) = 0; 
  virtual ~Observer() = default;
};

#endif
