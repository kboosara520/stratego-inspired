#include "subject.h"

void Subject::attach(Observer *o) {
        observers.emplace_back(o);
}
    
void Subject::detach(Observer *o) {  // Remove from observers
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == o) {
            observers.erase(it);
            return;
        }
    }
}

void Subject::notifyObservers() const {
    for (auto o : observers) {
        o->displayBoard();
    }
}

// Subject::~Subject() {}
