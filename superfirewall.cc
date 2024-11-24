#include "superfirewall.h"

SuperFireWall::SuperFireWall(int owner, std::unique_ptr<Tile> next, Player *player): Decorator{std::move(next)}, owner{owner}, powner{player} {}

void SuperFireWall::activate() {
    if (l != nullptr) {
        // if trojan remove the trojan ability
        if (l->getIsTrojan()) {
            l->setIsTrojan(false);
        }
        next->activate(); //should be fine as all l's should be poiting at same link;
        // since the firewall or server port will be changing the link;
        if (l->getIsDead()) {
            l = nullptr;
        }
    }
}

char SuperFireWall::charAt() {
    next->charAt();
}
