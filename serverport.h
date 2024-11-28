#ifndef SERVERPORT_H
#define SERVERPORT_H
#include "decorator.h"
#include "player.h"
#include "constants.h"

class ServerPort: public Decorator {
    int owner; // player index value
    const std::vector<Player *> &players;
    public:
        ServerPort(int owner, std::unique_ptr<Tile> next, const std::vector<Player *> &players); // just calls decorator constructor
        
        // downloads owners link on opponents server port
        void activate() override;
        
        // display S for server port, add S to constants file
        char charAt() override;
};

#endif
