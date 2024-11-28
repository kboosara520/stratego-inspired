#include "basetile.h"

BaseTile::BaseTile(Link * l): Tile{l}{}
void BaseTile::activate() {
    return;
}
void BaseTile::updateLink(Link * other) {
    l = other;
}
char BaseTile::charAt() {
    if (l == nullptr) {
        return '.';
    } else {
        return l->getName();
    }
}
