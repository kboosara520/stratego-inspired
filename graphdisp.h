#include "observer.h"
#include "board.h"
#include "window.h"

class graphDisp: public Observer {
    private:
    Board* Board;
    Xwindow * xw; 
    int top, bottom, left, right, tick;

    public:
        graphDisp(Studio* studio, Xwindow * xw,int top, int bottom, int left, int right, int tick); 
        void notify() override; 
        ~graphDisp(); 
};