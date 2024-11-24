#include "gamecontroller.h"

GameController::GameController(std::vector<std::string> playerAbilities, std::vector<std::string> linkFiles, std::istream *in, std::ostream &out): in{in}, out{out} {
    players.reserve(PLAYERCOUNT);
    for (int i = 0; i < PLAYERCOUNT; ++i) {
        players.emplace_back(std::make_unique<Player>(i, playerAbilities[i], linkFiles[i]));
    }
    board = std::make_unique<Board>(players, this);
}

int GameController::findWinner() {
    int activeCount = 0;
    for (int i = 0; i < players.size(); ++i) {
        if (players[i]->wins()) {
            return i;
        }
        players[i]->checkLoss();
        if (players[i]->isActive()) ++activeCount;
    }

    if (activeCount == 1) {
        for (int i = 0; i < players.size(); ++i) {
            if (players[i]->isActive()) return i; 
        }
    }
    return -1;
}

void GameController::runGame() {
    std::string command;
    bool winnerFound = false;
    int winner = -1;
    while(*in >> command) {
        if (command == "move") {
            // check if link is dead
            turn = (turn + 1) % PLAYERCOUNT; // updates whose turn it is
        }
        else if (command == "abilities") {
            out << players[turn]->getAbilities() << std::endl;;
        }
        else if (command == "ability") {
            // check if link is dead
            winner = findWinner();
            if (winner >= 0) break;
        }
        else if (command == "board") {
            board->display(turn);
        }
        else if (command == "sequence") {
            std::string fileName;
            *in >> fileName;
            file.open(fileName);
            if (file.is_open()) {
                in = &file;
                break;
            }
            else {
                out << "Unable to open the file" << std::endl;
                continue;
            }
        }
        else if (command == "quit") {
            break;
        }
        else {
            out << "Invalid command" << std::endl;
            continue;
        }
        winner = findWinner();
        if (winner >= 0) break;
    }
    if (winner >= 0) {
        out << "Player " << winner + 1 << " wins" << std::endl;
    }
}

int GameController::getTurn() { return turn; }
