#include "clientdisp.h"

ClientDisp::ClientDisp(Board *board, std::vector<Player *> players): board{board}, players{players} {}

std::string ClientDisp::displayBoard(int playerId) {
    auto &p1Links = players[0]->getLinks(); //std::map<char,std::unique_ptr<Link>> links;
    auto &p2Links = players[1]->getLinks();

    stringstream ss;
    ss << "Player 1" << endl;
    ss << "Downloaded: " << players[0]->getData() << "D, " << players[0]->getVirus() <<"V" << endl;
    ss << "Abilities: " << players[0]->getAbilityCount() << std::endl;

    for (int i = 0; i < BOARDSIZE/4; i++) {
        for (int j = 0; j < BOARDSIZE/2; j++) {
            
            // if its player 1's turn or the piece is visible, display piece
            // otherwise show as question mark
            char index = 'a' + (i * 4) + j;
            ss << p1Links.at(index)->getName() << " ";
            if (playerId % 2 == 0) {
                ss << p1Links.at(index)->getType() << p1Links.at(index)->getStrength() << " ";
            } 
            else if (p1Links.at(index)->getIsVisble()) {
                ss << p1Links.at(index)->getAppearsAs() << p1Links.at(index)->getStrength() << " ";
            }
            else {
                ss << "?  ";
            }
        }
        ss << endl;
    }

    ss << "========" << endl;
    for (int i = 0; i < BOARDSIZE; i++) {
        for (int j = 0; j < BOARDSIZE; j++) {
            ss << board->getState(j, i);
        }
        ss << endl;
    }
    ss << "========" << endl;
    ss << "Player 2" << endl;
    ss << "Downloaded: " << players[1]->getData() << "D, " << players[1]->getVirus() <<"V" << endl;
    ss << "Abilities: " << players[1]->getAbilityCount() << endl;

    for (int i = 0; i < BOARDSIZE/4; i++) {
        for (int j = 0; j < BOARDSIZE/2; j++) {
            char index = 'A' + (i * 4) + j;
            ss << p2Links.at(index)->getName() << " ";
            if (playerId % 2 == 1) {
                ss << p2Links.at(index)->getType() << p2Links.at(index)->getStrength() << " ";
            }
            else if (p2Links.at(index)->getIsVisble()) {
                ss << p2Links.at(index)->getAppearsAs() << p2Links.at(index)->getStrength() << " ";
            }
            else {
                ss << "?  ";
            }
        }
        if (i != BOARDSIZE / 4 - 1) ss << endl;
    }
    return ss.str();
}
