#include "serverport.h"

ServerPort::ServerPort(int owner, std::unique_ptr<Tile> next, const std::vector<Player *> &players): Decorator{std::move(next)}, owner{owner}, players{players}{}

char ServerPort::charAt() {
    return SERVERPORTNAME;
}

// Note:  Downloading a link must update the appropriate counters. It is up to you as to whether or not the link’s value is revealed.
void ServerPort::activate() {
    Player *powner = players[owner];
    if (l != nullptr) {
        l->setIsVisble(true);
        l->setIsDead(true);
        if (l->getType() == DATA) {
            powner->setData(powner->getData() + 1);
        } else {
            powner->setVirus(powner->getVirus() + 1); 
        }
        setLink(nullptr); //should set link to nullptr and apply recursively
    }
}

