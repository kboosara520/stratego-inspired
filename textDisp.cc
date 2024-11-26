#include "textDisp.h"
using namespace std;

TextDisp::TextDisp(Board * board, std::vector<Player *> players): board{board}, players{players}{}
void TextDisp::displayBoard() {
    
    // MAY NEED TO CHECK IF ITS A TROJAN, HAVE A DIFFERENT OUTPUT

    // have a method that returns a reference to the links owned by the player
    auto &p1Links = players[0]->getLinks(); //std::map<char,std::unique_ptr<Link>> links;
    auto &p2Links = players[1]->getLinks();
    cout << "Player 1" << endl;
    cout << "Downloaded: " << players[0]->getData() << "D, " << players[0]->getVirus() <<"V" << endl;
    cout << "Abilities: " << players[0]->getAbilityCount() << endl;

    for (int i = 0; i < BOARDSIZE/2; i++) {
        for (int j = 0; j < BOARDSIZE/2; j++) {
            
            // if its player 1's turn or the piece is visible, display piece
            // otherwise show as question mark
            char index = 'A' + i + j;
            cout << p1Links[index]->getName() << " ";
            if (ticks % 2 == 0 || p1Links[index]->isVisble()) {
                cout << p1Links[index]->getType() << p1Links[index]->getStrength() << " ";
            } else {
                cout << "?  ";
            }
        }
        cout << endl;
    }

    cout << "========" << endl;
    for (int i = 0; i < BOARDSIZE; i++) {
        for (int j = 0; j < BOARDSIZE; j++) {
            cout << board->getState(i, j);
        }
        cout << endl;
    }
    cout << "========" << endl;
    cout << "Player 2" << endl;
    cout << "Downloaded: " << players[1]->getData() << "D, " << players[1]->getVirus() <<"V" << endl;
    cout << "Abilities: " << players[1]->getAbilityCount() << endl;

    for (int i = 0; i < BOARDSIZE/2; i++) {
        for (int j = 0; j < BOARDSIZE/2; j++) {
            char index = 'a' + i + j;
            cout << p1Links[index]->getName() << " ";
            if (ticks % 2 == 1 || p2Links[index]->isVisble()) {
                cout << p2Links[index]->getType() << p2Links[index]->getStrength() << " ";
            } else {
                cout << "?  ";
            }
        }
        cout << endl;
    }
    ticks += 1;
}
