#include "textDisp.h"

TextDisp::TextDisp(Board * board, std::vector<Player *> players): board{board}, players{players}{}
void TextDisp::displayBoard() {
    
    // need to get a map of the links from the player.
    cout << "Player 1" << endl;
    cout << "Downloaded: " << players[0]->getData() << "D, " << players[0]->getVirus() <<"V" << endl;
    cout << "Abilities: " << players[0]->getAbilityCount() << endl;

    // handle printing individual pieces here
    // have a range based for loop
    for (int i = 0; i < BOARDSIZE/2; i++) {
        for (int j = 0; j < BOARDSIZE/2; j++) {
            // if its player 1's turn or the piece is visible, display piece
            // otherwise show as question mark
        }
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

    // handle printing individual pieces here
    // have a range based for loop
    for (int i = 0; i < BOARDSIZE/2; i++) {
        for (int j = 0; j < BOARDSIZE/2; j++) {
            // if its player 2's turn or the piece is visible, display piece
            // otherwise show as question mark
        }
    }
}
