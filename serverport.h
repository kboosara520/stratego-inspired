#ifndef SERVERPORT_H
#define SERVERPORT_H
#include "decorator.h"
#include "player.h"

class ServerPort: public Decorator {
    int owner; // player index value
    Player *powner;
    public:
        ServerPort(int owner, std::unique_ptr<Tile> next, Player *player); // just calls decorator constructor
        
        // downloads owners link on opponents server port
        void activate() override;
        
        // display S for server port, add S to constants file
        char charAt() override;
};

#endif