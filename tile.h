#ifndef TILE_H
#define TILE_H
#include "link.h"

class Tile {
    public:
        virtual char charAt() = 0;
        virtual void activate() = 0;
        virtual void updateLink(Link * other) = 0;
        void setLink(Link * other);
        Link * getLink();
        virtual ~Tile() = default;

    protected:
        Tile(Link * l = nullptr);
        Link * l;
};

#endif
