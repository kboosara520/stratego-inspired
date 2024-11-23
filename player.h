#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <memory>
#include <utility>
#include "constants.h"
#include "link.h"

class Player {
    std::vector<std::unique_ptr<Link>> links;
    // to print player's abilities: the index would be the key (index 0 -> ability1, index 1 -> ability 2)
    // the int in the pair is the ability id, and the bool indicates if it's still available or not
    std::vector<std::pair<char, bool>> abilities;
    const int playerId;
    int abilityCount;
    int data = 0;
    int virus = 0;

  public:
    Player(int id, std::string abilityList, std::string linkFile);
    int getPlayerId();
    int getAbilityCount();
    void setAbilityCount();
    int getData();
    void setData();
    int getVirus();
    void setVirus();
};

#endif
