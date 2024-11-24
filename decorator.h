#ifndef DECORATOR_H
#define DECORATOR_H

#include <memory>
#include "tile.h"

class Decorator: public Tile {
    protected:
        std::unique_ptr<Tile> next; // building layers on the tile
        Decorator(Tile * next);
        void updateLink(); // recursively updates all the links
};

#endif  