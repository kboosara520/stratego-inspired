#include "gamecontroller.h"

GameController::GameController(std::vector<std::string> playerAbilities, std::vector<std::string> linkFiles, std::istream *in, std::ostream &out): in{in}, out{out} {
    players.reserve(PLAYERCOUNT);
    for (int i = 0; i < PLAYERCOUNT; ++i) {
        players.emplace_back(std::make_unique<Player>(i, playerAbilities[i], linkFiles[i]));
        rplayers.emplace_back(players[i].get());
    }
    board = std::make_unique<Board>(players, turn);
    observers.emplace_back(std::make_unique<TextDisp>(board.get(), rplayers));

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

Move GameController::getMove(std::istream &s) {
    char name;
    char dir;
    s >> name >> dir;
    if (!s) throw IllegalMoveException{"Invalid input"};
    if (!players[turn]->ownsLink(name)) {
        throw IllegalMoveException{"The player does not own the link"};
    }
    if (players[turn]->linkIsDead(name)) {
        throw IllegalMoveException{"The Link is dead"};
    }
    return {name, dir};
}

char GameController::getOwnLinkName(std::istream &s) {
    char name;
    s >> name;
    if (!players[turn]->ownsLink(name)) {
        throw IllegalAbilityUseException{"The player does not own the link"};
    }
    if (players[turn]->linkIsDead(name)) {
        throw IllegalAbilityUseException{"The Link is dead"};
    }
    return name;
}

Coords GameController::getCoords(std::istream &s) {
    int x, y;
    s >> y >> x;
    if (!(x >= 0 && y >= 0 && x < BOARDSIZE && y < BOARDSIZE)) {
        throw IllegalAbilityUseException{"Coordinates out of bounds"};
    }
    return {x, y};
}

void GameController::runGame() {
    std::string command;
    int winner = -1;
    std::string line;
    while(getline(*in, line)) {
        std::istringstream s{line};
        s >> command;
        // std::cout << command << std::endl;
        if (command == "move") {
            bool fail = false;
            while (true) {
                char andOneName = '0';
                try {
                    if (fail) {
                        s.clear();
                        s.str(line);
                    }
                    Move move = getMove(s);
                    if (andOneName != '0' && move.name != andOneName) {
                        throw IllegalAbilityUseException{"Must move the same link"};
                    }
                    board->move(move.dir, move.name);
                    break;
                } 
                catch (const IllegalMoveException &e) {
                    std::string msg = e.what();
                    if (msg.size() == 1) {
                        board->display(turn);
                        std::cout << "AND ONE!" << std::endl;
                        andOneName = msg[0];
                    }
                    else {
                        out << e.what() << std::endl;
                    }
                    fail = true;
                    out << "Enter another move: " << std::endl;
                    getline(*in, line);
                    continue;
                }
            }
            turn = (turn + 1) % PLAYERCOUNT; // updates whose turn it is
            winner = findWinner();
            if (winner >= 0) break;
            board->display(turn);
        }
        else if (command == "abilities") {
            out << players[turn]->getAbilities() << std::endl;
        }
        else if (command == "ability") {
            int abId;
            s >> abId;
            if (abId < 1) {
                out << "Invalid ability ID (1-5)" << std::endl;
                in->clear();
                in->ignore();
                continue;
            }
            --abId; // get the index of the vector
            auto abilities = players[turn]->getAbilities();
            auto abPair = abilities[abId];
            if (!abPair.second) {
                out << "Ability has been used" << std::endl;
                continue;
            }
            if (abPair.first == POLARIZE) {
                char name;
                s >> name;
                try {
                    board->polarize(name);
                }
                catch (const IllegalAbilityUseException &e) {
                    out << e.what() << std::endl;
                    continue;
                }
            }
            else if (OWNLINKABILITIES.count(abPair.first) > 0) {
                char name;
                try {
                    name = getOwnLinkName(s);
                }
                catch (const IllegalAbilityUseException &e) {
                    out << e.what() << std::endl;
                    continue;
                }
                switch (abPair.first) {
                    case 'L':
                        players[turn]->boostLink(name);
                        break;
                    case 'T':
                        players[turn]->addTrojan(name);
                        break;
                    case 'A':
                        players[turn]->addAndOne(name);
                        break;
                    default:
                        break;
                }
            }
            else if (OPPLINKABILITIES.count(abPair.first) > 0) {
                char name;
                s >> name;
                if (players[turn]->ownsLink(name)) {
                    out << "Cannot use " << CHAR2NAME.at(abPair.first) << " on your own link" << std::endl;
                    continue;
                }
                try {
                    switch (abPair.first) {
                        case 'D':
                            board->download(turn, name);
                            break;
                        case 'S':
                            board->scan(name);
                            break;
                    }
                }
                catch (const IllegalAbilityUseException &e) {
                    cout << e.what() << std::endl;
                    continue;
                }
            }
            else {
                Coords coords;
                try {
                    coords = getCoords(s);
                }
                catch (const IllegalAbilityUseException &e) {
                    out << e.what() << std::endl;
                    continue;
                }
                // call board to apply effects
                switch (abPair.first) {
                    case 'F':
                        board->make_firewall(coords.x,coords.y);
                        break;
                    case 'W':
                        board->make_super_firewall(coords.x, coords.y);
                        break;
                    default:
                        break;
                }
            }
            players[turn]->useAbility(abId);
            winner = findWinner();
            if (winner >= 0) break;
        }
        else if (command == "board") {
            board->display(turn);
        }
        else if (command == "sequence") {
            std::string fileName;
            s >> fileName;
            file.open(fileName);
            if (file.is_open()) {
                in = &file;
            }
            else {
                out << "Unable to open the file" << std::endl;
            }
        }
        else if (command == "quit") {
            break;
        }
        else {
            out << "Invalid command" << std::endl;
        }
    }
    if (winner >= 0) {
        board->display(turn);
        out << "Player " << winner + 1 << " wins" << std::endl;
    }
}

int GameController::getTurn() { return turn; }
