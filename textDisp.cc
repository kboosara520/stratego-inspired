#include "textDisp.h"

TextDisp::TextDisp(Board * board): board{board}{}
void TextDisp::displayBoard() {
    // need to get the vector of players as a constant
    cout << "Player 1" << endl;
    cout << "Downloaded: " << endl; // get download and virus count of player 1
    cout << "Abilities" << endl;
    // handle printing individual pieces
    cout << "========" << endl;
    for (int i = 0; i < BOARDSIZE; i++) {
        for (int j = 0; j < BOARDSIZE; j++) {
            cout << board->getState(i, j);
        }
        cout << endl;
    }
    cout << "========" << endl;

}
