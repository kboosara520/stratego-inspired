#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Observer {
 public:
  virtual void displayBoard(int turn) = 0; 
  virtual ~Observer() = default;
};

#endif
