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
    std::unique_ptr<ClientDisp> display;
    const int getConnectionsTimeout = 30;
    bool hasData = false;
    std::atomic<bool> timeout = false;
    void getConnections(socklen_t sinSize, sockaddr_storage &connectorAddr, int &acceptorSocket, char address[]);
    void checkStatus();
    void recvFromPlayer(int &sockFd);
    void clearClientSockets();
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
    void sendBoardToPlayers();
    void endGame(int winnerId);
};

#endif
