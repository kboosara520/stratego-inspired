#include "gamecontroller.h"

GameController::GameController(std::vector<std::string> playerAbilities, std::vector<std::string> linkFiles) {
    players.reserve(PLAYERCOUNT);
    for (int i = 0; i < PLAYERCOUNT; ++i) {
        players.emplace_back(std::make_unique<Player>(i, playerAbilities[i], linkFiles[i]));
    }
    board = std::make_unique<Board>(players, this);
}
