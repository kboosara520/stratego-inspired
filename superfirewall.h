#ifndef SUPERFIREWALL_H
#define SUPERFIREWALL_H
#include "decorator.h"

class SuperFireWall: public Decorator {
    int owner;
    public:
        SuperFireWall(); // just calls decorator constructor
        void activate() override;
        char charAt() override;
};

#endif