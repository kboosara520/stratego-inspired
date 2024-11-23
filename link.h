#ifndef LINK_H
#define LINK_H

class Link {
    char name;
    char type; //v for virus, d for data
    int strength;
    int movement;
    int owner; // uses players index in GameController
    bool isVisible;
    bool isDead;
    bool isTrojan;
    bool isAndOne;
    
    public:
        Link(char name, char type, int strength, int owner, int movement = 1, bool isVisible = true, bool isDead = false);
        char getName();
};

#endif