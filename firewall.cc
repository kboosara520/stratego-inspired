#include "firewall.h"

Firewall::Firewall(int owner, std::unique_ptr<Tile> next): Decorator{std::move(next)}, owner{owner} {}
char Firewall::charAt() {
    if (l != nullptr) {
        return l->getName();
    } else {
        return FIREWALLNAMES[owner];
    }
}
void Firewall::activate() {
    if (l != nullptr) {
        if (l->getOwner() != owner) {
            // link should be revealed
            // if virus, downloaded 
        }
    }
}

//         //should check to see if there is a link on the tile
//         // if trojan reveal as data (actually a virus)
//         //if enemy link reveal it, AND if virus download to owner
//         // call next's activate
//         void activate() override; 
//