#include "tile.h"
#include "link.h"

Tile::Tile(Link * l): l{l}{}
void Tile::setLink(Link * other) { l = other;}
Link * Tile::getLink() {return l;}
