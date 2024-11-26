#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include "board.h"
#include "constants.h"
#include "player.h"
#include "illegalmoveexception.h"
#include "illegalabilityuseexception.h"

struct Move {
    char name;
    char dir;
};

struct Coords {
    int x, y;
};

class GameController {
    std::istream *in;
    std::ifstream file;
    std::ostream &out;
    std::vector<std::unique_ptr<Player>> players;
    std::unique_ptr<Board> board;
    int turn = 0;
    int findWinner();
    Move getMove();
    char getLinkName();
    Coords getCoords();
  public:
    GameController(
      std::vector<std::string> playerAbilities, 
      std::vector<std::string> linkFiles, 
      std::istream *in = &std::cin, 
      std::ostream &out = std::cout
    );
    int getTurn();
    void runGame();
};

#endif
