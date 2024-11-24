#ifndef FIREWALL_H
#define FIREWALL_H
#include "decorator.h"
#include "constants.h"
#include "player.h"
#include <memory>

class Firewall: Decorator {
    
    int owner; //index of the player that owns the firewall
    Player *powner;

    public:
        Firewall(int owner, std::unique_ptr<Tile> next, Player *player);

        //should check if there is a link, if owner's link display it, otherwise display firewall. 
        //How to determine char to be displayed for firewall?
        char charAt() override; 

        //should check to see if there is a link on the tile
        // if trojan reveal as data (actually a virus)
        //if enemy link reveal it, AND if virus download to owner
        // call next's activate
        void activate() override; 
};

#endif