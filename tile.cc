#include "tile.h"
#include "link.h"

Tile::Tile(Link * l): l{l}{}

void Tile::setLink(Link * other) { updateLink(other);}
Link * Tile::getLink() {return l;}
