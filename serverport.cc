#include "serverport.h"

ServerPort::ServerPort(int owner, std::unique_ptr<Tile> next, Player *player): Decorator{std::move(next)}, owner{owner}, powner{player}{}

char ServerPort::charAt() {
    return SERVERPORTNAME;
}

// Note:  Downloading a link must update the appropriate counters. It is up to you as to whether or not the link’s value is revealed.
void ServerPort::activate() {
    if (l != nullptr) {
        l->setIsVisble(true);
        l->setIsDead(true);
        if (l->getType() == 'd') {
            powner->setData(powner->getData() + 1);
        } else {
           powner->setVirus(powner->getVirus() + 1); 
        }
        setLink(nullptr); //should set link to nullptr and apply recursively
    }
}

