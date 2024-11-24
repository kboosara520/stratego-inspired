#ifndef SERVERPORT_H
#define SERVERPORT_H
#include "decorator.h"

class ServerPort: public Decorator {
    int owner;
    public:
        ServerPort(std::unique_ptr<Tile> next); // just calls decorator constructor
        void activate() override;
        char charAt() override;
};

#endif