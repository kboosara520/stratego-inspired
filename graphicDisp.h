#ifndef GRAPHIC_DISP_H
#define GRAPHIC_DISP_H

#include <memory>
#include <string>
#include <vector>
#include "observer.h"
#include "board.h"
#include "constants.h"
#include "player.h"
#include "window.h"

class GraphicDisp: public Observer {
    Board *board;
    std::vector<Player *> players;
    std::unique_ptr<Xwindow> window;
    int getColour(Link *link, int turn);
  public:
    GraphicDisp(Board *board, std::vector<Player *>players);
    ~GraphicDisp();
    void displayBoard(int turn, const std::vector<std::pair<int, int>> &changes);
};

#endif
