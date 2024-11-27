#include "link.h"
Link::Link(char name, char type, int strength, int owner, int movement, bool isVisible, bool isDead, bool isTrojan, bool isAndOne):name{name}, type{type}, appearsAs{type}, strength{strength}, movement{movement}, owner{owner}, isVisible{isVisible}, isDead{isDead}, isTrojan{isTrojan}, isAndOne{isAndOne}{}
char Link::getName() {
    return name;
}
char Link::getType() {
    return type;
}
char Link::getAppearsAs() {
    return appearsAs;
}
int Link::getOwner() {
    return owner;
}
int Link::getMovement() {
    return movement;
}
int Link::getStrength() {
    return strength;
}
bool Link::getIsTrojan() {
    return isTrojan;
}
bool Link::getIsDead() {
    return isDead;
}
bool Link::getIsVisble() {
    return isVisible;
}
bool Link::getIsAndOne() {
    return isAndOne;
}
void Link::setIsVisble(bool isVisible) {
    this->isVisible = isVisible;
}
void Link::setIsDead(bool isDead) {
    this->isDead = isDead;
}
void Link::setMovement(int movement) {
    this->movement = movement;
}
void Link::setIsTrojan(bool isTrojan) {
    this->isTrojan = isTrojan;
    if (isTrojan) {
        if (this->type == VIRUS) {
            this->appearsAs = DATA;
        }
        else {
            this->appearsAs = VIRUS;
        }
    }
}

void Link::superReveal() {
    this->appearsAs = this->type;
}

void Link::setIsAndOne(bool isAndOne) {
    this->isAndOne = isAndOne;
}

void Link::setType(char type) {
    this->type = type;
}

void Link::polarize() {
    if (this->type == DATA) this->type = VIRUS;
    else this->type = DATA;
}
