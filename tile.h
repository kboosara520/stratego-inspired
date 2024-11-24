#ifndef TILE_H
#define TILE_H
#include "link.h"

class Tile {
    public:
        virtual char charAt() = 0;
        virtual void activate() = 0;
        void setLink(Link * other);
        Link * getLink();
    protected:
        Link * l;
        Tile(Link * l = nullptr);
};

#endif