#include "player.h"

Player::Player(int id, std::string abilityList, std::string linkFile): playerId{id} {
    abilities.reserve(abilityList.size());
    for (int i = 0; i < abilityList.size(); ++i) {
        abilities.emplace_back(abilityList[i], true);
    }
    links.reserve(LINKCOUNT);
    // create links
    // for (int i = 0; i < LINKCOUNT; ++i) {
    //     links.emplace_back(std::make_unique<Link>(LINKNAMES[playerId] + i, ));
    // }
}


