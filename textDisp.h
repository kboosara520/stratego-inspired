#ifndef TEXT_DISP_H
#define TEXT_DISP_H

#include "observer.h"
#include "board.h"
#include "constants.h"
#include "player.h"
#include <iostream>

class TextDisp: public Observer {
        // any private fields 
        Board* board;
        std::vector<Player *> players;
    public:
        //constructor 
        TextDisp(Board * board, std::vector<Player *> players); 
        ~TextDisp();
        void displayBoard(int turn, const std::vector<std::pair<int, int>> &changes); 
};

#endif
