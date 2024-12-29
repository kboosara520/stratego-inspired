#ifndef SERVER_H
#define SERVER_H

#include "networking.h"
#include "constants.h"
#include "serverinitexception.h"

class Server {
    int &turn;
    std::vector<int> clientSockets;
    std::thread mainServerThread;
    std::vector<std::thread> threads;
    std::stringstream &controllerStream;
    void recvFromPlayer(int &sockFd);
  public:
    Server(std::stringstream &controllerStream, int &turn);
    void run();
};

void sigchld_handler(int s);
void *get_in_addr(sockaddr *sa);
void closeSocket(int &sockFd);

#endif
