#include "player.h"

Player::Player(int id, std::string abilityList, std::string linkFile): playerId{id} {
    abilities.reserve(abilityList.size());
    for (int i = 0; i < abilityList.size(); ++i) {
        abilities.emplace_back(abilityList[i], true);
    }
    links.reserve(LINKCOUNT);
    std::ifstream file{linkFile};
    if (file.is_open()) {
        for (int i = 0; i < LINKCOUNT; ++i) {
            char type;
            char strength;
            file >> type >> strength;
            links.emplace_back(std::make_unique<Link>(
                LINKNAMES[playerId] + i,
                type,
                strength - '0',
                playerId
            ));
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
            links.emplace_back(std::make_unique<Link>(
                LINKNAMES[playerId] + i,
                types[i],
                strengths[i],
                playerId
            ));
        }
    }
}


