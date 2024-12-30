#ifndef SERVER_H
#define SERVER_H

#include "player.h"
#include "board.h"
#include "networking.h"
#include "constants.h"
#include "clientdisp.h"
#include "serverinitexception.h"

class Server {
    std::mutex mtx;
    std::vector<int> clientSockets;
    std::vector<std::thread> threads;
    std::stringstream &controllerStream;
    int &turn;
    std::condition_variable &controllerCv;
    ClientDisp display;
    bool hasData = false;
    void recvFromPlayer(int &sockFd);
  public:
    Server(
        std::stringstream *controllerStream, 
        int &turn, 
        std::condition_variable &controllerCv, 
        Board *board, 
        std::vector<Player *> players
    );
    void run();
    bool dataReady();
    void consumeData();
    void sendToPlayer(int turn, int cmd, const std::string &str);
    void broadcast(int cmd, const std::string &str);
};

#endif
