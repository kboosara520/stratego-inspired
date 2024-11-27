#include "superfirewall.h"

SuperFireWall::SuperFireWall(int owner, std::unique_ptr<Tile> next): Decorator{std::move(next)}, owner{owner} {}

void SuperFireWall::activate() {
    if (l && owner != l->getOwner()) {
        // if trojan remove the trojan ability
        l->superReveal();
        l->setIsTrojan(false);
    }
    next->activate();
    if (l->getIsDead()) {
        setLink(nullptr);
    }
}

char SuperFireWall::charAt() {
    return next->charAt();
}
