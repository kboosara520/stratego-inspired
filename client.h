#ifndef CLIENT_H
#define CLIENT_H

#include "networking.h"
#include "clientinitexception.h"

class Client {
    int playerId = -1; // -1 at initialization
    int sockFd;
    std::atomic<bool> gameRunning = false;
    void recvFromServer();
  public:
    Client();
    void run();
};

#endif
