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
#include "observer.h"
#include "server.h"
#include "serverinitexception.h"
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
    std::ostream &out = std::cout;
    std::vector<std::unique_ptr<Player>> players;
    std::vector<Player *> rplayers;
    std::unique_ptr<Board> board;
    std::vector<std::unique_ptr<Observer>> observers;
    int turn = 0;
    std::unique_ptr<Server> server;
    std::thread serverThread;
    std::mutex controllerMtx;
    std::condition_variable cv;
    int findWinner();
    Move getMove(std::istream &s);
    char getOwnLinkName(std::istream &s);
    Coords getCoords(std::istream &s);
    std::istream &getLineFromInput(std::string &str);
  public:
    GameController(
      std::vector<std::string> playerAbilities, 
      std::vector<std::string> linkFiles,
      std::istream *in = &std::cin
    );
    int getTurn();
    void runGame();
};

#endif
