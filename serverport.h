#ifndef SERVERPORT_H
#define SERVERPORT_H
#include "decorator.h"

class ServerPort: public Decorator {
    int owner;
    public:
        ServerPort(); // just calls decorator constructor
        void activate() override;
        char charAt() override;
};

#endif