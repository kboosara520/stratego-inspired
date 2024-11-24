#ifndef PLAYER_H
#define PLAYER_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <random>
#include <map>
#include <utility>
#include "constants.h"
#include "link.h"

class Player {
    // std::vector<std::unique_ptr<Link>> links;
    std::map<char,std::unique_ptr<Link>> links; 
    // to print player's abilities: the index would be the key (index 0 -> ability1, index 1 -> ability 2)
    // the int in the pair is the ability id, and the bool indicates if it's still available or not
    std::vector<std::pair<char, bool>> abilities;

    const int playerId;
    int abilityCount;
    int data = 0;
    int virus = 0;

  public:
    Player(int id, std::string abilityList, std::string linkFile);
    void useAbility(int id);
    int getPlayerId();
    int getAbilityCount();
    void setAbilityCount(int n);
    int getData();
    void setData(int n);
    int getVirus();
    void setVirus(int n);
    bool wins();
    bool loses();
};

#endif
