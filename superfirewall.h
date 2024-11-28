#ifndef SUPERFIREWALL_H
#define SUPERFIREWALL_H
#include "decorator.h"
#include "player.h"

class SuperFireWall: public Decorator {
    int owner;
    public:
        SuperFireWall(int owner, std::unique_ptr<Tile> next);
        
        // able to detect trojans
        // call next's activate
        void activate() override;

        // what should this return
        char charAt() override;
};

#endif
