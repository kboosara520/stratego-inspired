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

int Player::getPlayerId() const { return playerId; }

int Player::getAbilityCount() const { return abilityCount; }

void Player::setAbilityCount(int n) { abilityCount = n; }

int Player::getData() const { return data; }

void Player::setData(int n) { data = n; }

int Player::getVirus() const { return virus; }

void Player::setVirus(int n) { virus = n; }

bool Player::wins() const { return data >= WINCONDITION; }

void Player::checkLoss() {
    if (virus >= WINCONDITION) active = false;
}

bool Player::isActive() const { return active; }

const std::vector<std::pair<char, bool>> &Player::getAbilities() const { return abilities; }

const std::map<char, std::unique_ptr<Link>> &Player::getLinks() const { return links; }

bool Player::ownsLink(char name) const { return links.count(name) > 0; }

bool Player::linkIsDead(char name) const { return links.at(name)->getIsDead(); }

void Player::boostLink(char name) {
    links[name]->setMovement(2);
}

void Player::polarize(char name) {
    Link *link = links[name].get();
    char type = link->getType();
    if (type == DATA) link->setType(VIRUS);
    else link->setType(DATA);
}

void Player::addTrojan(char name) {
    links[name]->setIsTrojan(true);
}

void Player::addAndOne(char name) {
    links[name]->setIsAndOne(true);
}

std::ostream &operator<<(std::ostream &out, const std::vector<std::pair<char, bool>> &abilities) {
  for (int i = 0; i < abilities.size(); ++i) {
    out << i + 1 << ": " << CHAR2NAME.at(abilities[i].first) << ", available(not used): ";
    if (abilities[i].second) {
        out << "true";
    }
    else {
        out << "false";
    }
    out << std::endl;
  }
  return out;
}