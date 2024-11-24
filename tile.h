#ifndef TILE_H
#define TILE_H
#include "link.h"

class Tile {
    public:
        virtual char charAt() = 0;
        virtual void activate() = 0;
    protected:
        Link * l;
        void setLink(Link * other);
        Link * getLink();
        Tile(Link * l = nullptr);
};

#endif