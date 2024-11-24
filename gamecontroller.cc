#include "gamecontroller.h"

GameController::GameController(std::vector<std::string> playerAbilities, std::vector<std::string> linkFiles, std::istream &in, std::ostream &out): in{in}, out{out} {
    players.reserve(PLAYERCOUNT);
    for (int i = 0; i < PLAYERCOUNT; ++i) {
        players.emplace_back(std::make_unique<Player>(i, playerAbilities[i], linkFiles[i]));
    }
    board = std::make_unique<Board>(players, this);
}

void GameController::runGame() {
    std::string command;
    bool winnerFound = false;
    while(in >> command) {
        if (command == "move") {
            // check if link is dead

            turn = (turn + 1) % PLAYERCOUNT; // updates whose turn it is
        }
        else if (command == "abilities") {

        }
        else if (command == "ability") {
            // check if link is dead
        }
        else if (command == "board") {

        }
        else if (command == "sequence") {

        }
        else if (command == "quit") {
            break;
        }

        
    }
    if (winnerFound) {
        // print a message
    }
}

int GameController::getTurn() { return turn; }
