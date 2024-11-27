#include "superfirewall.h"

SuperFireWall::SuperFireWall(int owner, std::unique_ptr<Tile> next, const std::vector<Player *> &players): Decorator{std::move(next)}, owner{owner}, players{players} {}

void SuperFireWall::activate() {
    if (l && owner != l->getOwner()) {
        // if trojan remove the trojan ability
        l->superReveal();
        l->setIsTrojan(false);
         //should be fine as all l's should be poiting at same link;
        // since the firewall or server port will be changing the link;
    }
    next->activate();
    if (l->getIsDead()) {
        setLink(nullptr);
    }
}

char SuperFireWall::charAt() {
    return next->charAt();
}
