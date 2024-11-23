#include "observer.h"
#include "board.h"
#include <iostream>

class textDisp: public Observer {
        // any private fields 
        Board* board;
        int top, bottom, left, right; 
        int ticks = 0; 
    public:
        //constructor 
        textDisp(Board * board); 

        void drawBoard(Board* b) override; 
        void displayBoard(Board* b)override; 

        // destructor
        ~textDisp(); 
};