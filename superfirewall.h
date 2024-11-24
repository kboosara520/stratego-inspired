#ifndef SUPERFIREWALL_H
#define SUPERFIREWALL_H
#include "decorator.h"

class SuperFireWall: public Decorator {
    int owner;
    public:
        SuperFireWall(); // just calls decorator constructor
        
        // able to detect trojans
        // call next's activate
        void activate() override;

        // what should this return
        char charAt() override;
};

#endif