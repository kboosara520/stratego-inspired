#ifndef FIREWALL_H
#define FIREWALL_H
#include "decorator.h"

class Firewall: Decorator {
    
    int owner;
    public:
        Firewall();
        char charAt() override;
        void activate() override;
};

#endif