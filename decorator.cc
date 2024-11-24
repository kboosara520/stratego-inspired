#include "decorator.h"

Decorator::Decorator(std::unique_ptr<Tile> other) {
    next = std::move(other);
}
void Decorator::updateLink(Link * other) {
    l = other;
    next->updateLink(other);
}
