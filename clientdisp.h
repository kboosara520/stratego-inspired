#ifndef CLIENTDISP_H
#define CLIENTDISP_H

#include "player.h"
#include "board.h"
#include "constants.h"
#include <iostream>
#include <sstream>

using namespace std;

class ClientDisp {
    Board *board;
    vector<Player *> players;
  public:
    ClientDisp(Board *board, vector<Player *> players);
    ~ClientDisp() = default;
    std::string displayBoard(int playerId);
};

#endif
