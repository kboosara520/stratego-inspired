#include "observer.h"
#include "board.h"
#include "constants.h"
#include <iostream>

class TextDisp: public Observer {
        // any private fields 
        Board* board;
        int ticks = 0; 
    public:
        //constructor 
        TextDisp(Board * board); 
        void displayBoard(); 
};