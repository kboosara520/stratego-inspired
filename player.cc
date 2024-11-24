#include "player.h"

Player::Player(int id, std::string abilityList, std::string linkFile): playerId{id} {
    abilities.reserve(abilityList.size());
    for (int i = 0; i < abilityList.size(); ++i) {
        abilities.emplace_back(abilityList[i], true);
    }
    std::ifstream file{linkFile};
    if (file.is_open()) {
        for (int i = 0; i < LINKCOUNT; ++i) {
            char type;
            char strength;
            file >> type >> strength;
            links.emplace(
                LINKNAMES[playerId] + i,
                std::make_unique<Link>(
                    LINKNAMES[playerId] + i,
                    type,
                    strength - '0',
                    playerId      
                )
            );
        }
    }
    else { // randomizes the types and strengths if the file is not opened for any reason
        std::vector<int> strengths{1, 1, 2, 2, 3, 3, 4, 4};
        std::vector<char> types{DATA, DATA, DATA, DATA, VIRUS, VIRUS, VIRUS, VIRUS};
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(strengths.begin(), strengths.end(), g);
        std::shuffle(types.begin(), types.end(), g);
        for (int i = 0; i < LINKCOUNT; ++i) {
            links.emplace(
                LINKNAMES[playerId] + i,
                std::make_unique<Link>(
                    LINKNAMES[playerId] + i,
                    types[i],
                    strengths[i],
                    playerId
                )
            );
        }
    }
}

void Player::useAbility(int id) {
    // apply the ability's effect
    // set the ability's availability to false
    abilities[id - 1].second = false; 
}

int Player::getPlayerId() { return playerId; }

int Player::getAbilityCount() { return abilityCount; }

void Player::setAbilityCount(int n) { abilityCount = n; }

int Player::getData() { return data; }

void Player::setData(int n) { data = n; }

int Player::getVirus() { return virus; }

void Player::setVirus(int n) { virus = n; }

bool Player::wins() { return data >= WINCONDITION; }

bool Player::loses() { return virus >= WINCONDITION; }
