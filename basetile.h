#ifndef BASETILE_H
#define BASETILE_H
#include "tile.h"
#include "link.h"

class BaseTile: public Tile {
    public:
        BaseTile(Link * l = nullptr);
        void activate() override;
        char charAt() override;
        void updateLink(Link * other) override;
};

#endif