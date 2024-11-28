#include "textDisp.h"
using namespace std;

TextDisp::TextDisp(Board * board, std::vector<Player *> players): board{board}, players{players}{
    board->attach(this);
}

TextDisp::~TextDisp() {
    board->detach(this);
}

void TextDisp::displayBoard(int turn, const std::vector<std::pair<int, int>> &changes) {
    
    // MAY NEED TO CHECK IF ITS A TROJAN, HAVE A DIFFERENT OUTPUT
    // have a method that returns a reference to the links owned by the player
    auto &p1Links = players[0]->getLinks(); //std::map<char,std::unique_ptr<Link>> links;
    auto &p2Links = players[1]->getLinks();
    cout << "Player 1" << endl;
    cout << "Downloaded: " << players[0]->getData() << "D, " << players[0]->getVirus() <<"V" << endl;
    cout << "Abilities: " << players[0]->getAbilityCount() << endl;

    for (int i = 0; i < BOARDSIZE/4; i++) {
        for (int j = 0; j < BOARDSIZE/2; j++) {
            
            // if its player 1's turn or the piece is visible, display piece
            // otherwise show as question mark
            char index = 'a' + (i * 4) + j;
            cout << p1Links.at(index)->getName() << " ";
            if (turn % 2 == 0) {
                cout << p1Links.at(index)->getType() << p1Links.at(index)->getStrength() << " ";
            } 
            else if (p1Links.at(index)->getIsVisble()) {
                cout << p1Links.at(index)->getAppearsAs() << p1Links.at(index)->getStrength() << " ";
            }
            else {
                cout << "?  ";
            }
        }
        cout << endl;
    }

    cout << "========" << endl;
    for (int i = 0; i < BOARDSIZE; i++) {
        for (int j = 0; j < BOARDSIZE; j++) {
            cout << board->getState(j, i);
        }
        cout << endl;
    }
    cout << "========" << endl;
    cout << "Player 2" << endl;
    cout << "Downloaded: " << players[1]->getData() << "D, " << players[1]->getVirus() <<"V" << endl;
    cout << "Abilities: " << players[1]->getAbilityCount() << endl;

    for (int i = 0; i < BOARDSIZE/4; i++) {
        for (int j = 0; j < BOARDSIZE/2; j++) {
            char index = 'A' + (i * 4) + j;
            cout << p2Links.at(index)->getName() << " ";
            if (turn % 2 == 1) {
                cout << p2Links.at(index)->getType() << p2Links.at(index)->getStrength() << " ";
            }
            else if (p2Links.at(index)->getIsVisble()) {
                cout << p2Links.at(index)->getAppearsAs() << p2Links.at(index)->getStrength() << " ";
            }
            else {
                cout << "?  ";
            }
        }
        cout << endl;
    }
}
