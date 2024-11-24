#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "board.h"
#include "constants.h"
#include "player.h"

class GameController {
    std::istream &in;
    std::ostream &out;
    std::vector<std::unique_ptr<Player>> players;
    std::unique_ptr<Board> board;
    int turn = 0;
  public:
    GameController(std::vector<std::string> playerAbilities, std::vector<std::string> linkFiles, std::istream &in, std::ostream &out);
    int getTurn();
    void runGame();
};

#endif
