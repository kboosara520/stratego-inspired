#include "firewall.h"

Firewall::Firewall(int owner, std::unique_ptr<Tile> &&next, const std::vector<Player *> &players): Decorator{std::move(next)}, owner{owner}, players{players}{}
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
                if (l->getType() == DATA) {
                    l->setIsDead(true);
                    // powner->setVirus(powner->getVirus() + 1); // wrong player downloading the virus
                    Player *linkOwner = players[l->getOwner()];
                    linkOwner->setVirus(linkOwner->getVirus() + 1);
                    setLink(nullptr); // should set link to null and apply recursively
                } 
            }
            else if (l->getType() == VIRUS) {
                // if virus, download, increase virus count, remove link
                l->setIsDead(true);
                // powner->setVirus(powner->getVirus() + 1); // wrong player downloading the virus
                Player *linkOwner = players[l->getOwner()];
                linkOwner->setVirus(linkOwner->getVirus() + 1);
                setLink(nullptr);
            }
        }
    }
}
