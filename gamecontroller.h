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
#include "clientdisp.h"

using namespace std;

struct Move {
    char name, dir;
};

struct Coords {
    int x, y;
};

class GameController {
    istream *in;
    ifstream file;
    ostream &out = std::cout;
    vector<std::unique_ptr<Player>> players;
    vector<Player *> rplayers;
    unique_ptr<Board> board;
    vector<std::unique_ptr<Observer>> observers;
    int turn = 0;
    unique_ptr<Server> server;
    thread serverThread;
    mutex controllerMtx;
    condition_variable cv;
    stringstream sstream;
    int findWinner();
    Move getMove(std::istream &s);
    char getOwnLinkName(std::istream &s);
    Coords getCoords(std::istream &s);
    istream &getLineFromInput(std::string &str);
    void sendToClient();
  public:
    GameController(
      vector<std::string> playerAbilities, 
      vector<std::string> linkFiles,
      istream *in = &std::cin
    );
    int getTurn();
    void runGame();
};

#endif
