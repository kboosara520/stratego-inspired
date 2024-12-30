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
    std::condition_variable &controllerCv;
    bool hasData = false;
    void recvFromPlayer(int &sockFd);
  public:
    Server(std::stringstream *controllerStream, int &turn, std::condition_variable &controllerCv);
    void run();
    bool dataReady();
    void consumeData();
    void sendToPlayer(int turn, int cmd, const std::string &str);
    void broadcast(int cmd, const std::string &str);
};

#endif
