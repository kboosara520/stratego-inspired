#ifndef LINK_H
#define LINK_H

#include "constants.h"

class Link {
    char name;
    char type; //v for virus, d for data
    char appearsAs;
    int strength;
    int movement;
    int owner; // uses players index in GameController
    
    bool isVisible;
    bool isDead;
    bool isTrojan;
    bool isAndOne;
    
    public:
        Link(char name, char type, int strength, int owner, int movement = 1, bool isVisible = false, bool isDead = false, bool isTrojan = false, bool isAndOne = false);
        char getName();
        char getType();
        char getAppearsAs();
        int getOwner();
        int getMovement();
        int getStrength();
        bool getIsTrojan();
        bool getIsDead();
        bool getIsVisble();
        bool getIsAndOne();
        void setIsVisble(bool isVisible);
        void setIsDead(bool isDead);
        void setMovement(int movement);
        void setIsTrojan(bool isTrojan);
        void setIsAndOne(bool isAndOne);
        void setType(char type);
        void polarize();
        void superReveal();
};

#endif
