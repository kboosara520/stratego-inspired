#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Observer {
 public:
  virtual void displayBoard(Board* b) = 0; 
  virtual ~Observer() = default;
};

#endif
