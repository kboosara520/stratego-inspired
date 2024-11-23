#include "basetile.h"
#include "link.h"

BaseTile::BaseTile(Link * l): Tile{l}{}
void BaseTile::activate() {
    return;
}
char BaseTile::charAt() {
    if (l == nullptr) {
        return '.';
    } else {
        return l->getName();
    }
}