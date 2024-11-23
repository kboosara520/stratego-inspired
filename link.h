#ifndef LINK_H
#define LINK_H

class Link {
    char name;
    char type; //v for virus, d for data
    int strength;
    int movement;
    bool isVisible;
    bool isDead;
    
    Link(char name, char type, int strength, int movement = 1, bool isVisible = true, bool isDead = false);
};

#endif