#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "observer.h"

class Subject {
  std::vector<Observer *> observers;
 public:
  void attach( Observer* o );
  void detach( Observer* o );
  void notifyObservers() const;

  virtual ~Subject() = default;
};

#endif

/*

+notifyObservers(): void
+attach(Observer *o): void
+detach(Observer *o): void
+getState(): Player

*/