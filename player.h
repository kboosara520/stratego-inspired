#ifndef PLAYER_H
#define PLAYER_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <random>
#include <map>
#include <unordered_map>
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
    int abilityCount = 5;
    int data = 0;
    int virus = 0;
    bool active = true;

  public:
    Player(int id, std::string abilityList, std::string linkFile);
    void useAbility(int id);
    int getPlayerId() const;
    int getAbilityCount() const;
    void setAbilityCount(int n);
    int getData() const;
    void setData(int n);
    int getVirus() const;
    void setVirus(int n);
    bool wins() const;
    void checkLoss();
    bool isActive() const;
    bool ownsLink(char name) const;
    bool linkIsDead(char name) const;
    void boostLink(char name);
    void polarize(char name);
    void addTrojan(char name);
    void addAndOne(char name);
    const std::vector<std::pair<char, bool>> &getAbilities() const;
    const std::map<char, std::unique_ptr<Link>> &getLinks() const;
};

std::ostream &operator<<(std::ostream &out, const std::vector<std::pair<char, bool>> &abilities);

#endif
