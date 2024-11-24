#include "firewall.h"

Firewall::Firewall(int owner, std::unique_ptr<Tile> next, Player *player): Decorator{std::move(next)}, owner{owner}, powner{player}{}
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
            l->setIsVisble(true);
            if (l->getIsTrojan()) {
                // when a link dies, set the link pionter in tile to nullptr
                // if is data -> reveal, treat as virus and download
                // if virus -> reveal, treat as data and do nothing
                if (l->getType() == 'd') {
                    l->setIsDead(true);
                    powner->setVirus(powner->getVirus() + 1);
                    setLink(nullptr); // should set link to null and apply recursively
                } 
            }
            else if (l->getType() == 'v') {
                // if virus, download, increase virus count, remove link
                l->setIsDead(true);
                powner->setVirus(powner->getVirus() + 1);
                setLink(nullptr);
            }
        }
    }
}
