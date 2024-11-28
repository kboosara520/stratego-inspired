#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "board.h"
#include "constants.h"
#include "player.h"
#include "textDisp.h"
#include "graphicDisp.h"
#include "observer.h"
#include "illegalmoveexception.h"
#include "illegalabilityuseexception.h"

struct Move {
    char name, dir;
};

struct Coords {
    int x, y;
};

class GameController {
    std::istream *in;
    std::ifstream file;
    std::ostream &out;
    std::vector<std::unique_ptr<Player>> players;
    std::vector<Player *> rplayers;
    std::unique_ptr<Board> board;
    std::vector<std::unique_ptr<Observer>> observers;
    int turn = 0;
    int findWinner();
    Move getMove(std::istream &s);
    char getOwnLinkName(std::istream &s);
    Coords getCoords(std::istream &s);
  public:
    GameController(
      std::vector<std::string> playerAbilities, 
      std::vector<std::string> linkFiles,
      bool enableGraphics,
      std::istream *in = &std::cin, 
      std::ostream &out = std::cout
    );
    int getTurn();
    void runGame();
};

#endif
