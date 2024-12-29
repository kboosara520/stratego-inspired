#ifndef SERVER_H
#define SERVER_H

#include "networking.h"
#include "constants.h"
#include "serverinitexception.h"

class Server {
    std::mutex mtx;
    std::vector<int> clientSockets;
    std::vector<std::thread> threads;
    std::stringstream &controllerStream;
    int &turn;
    void recvFromPlayer(int &sockFd);
  public:
    Server(std::stringstream *controllerStream, int &turn);
    void run();
};

void sigchld_handler(int s);

#endif
