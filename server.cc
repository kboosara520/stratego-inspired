#include "server.h"

Server::Server(std::stringstream *controllerStream, int &turn): controllerStream{*controllerStream}, turn{turn} {
    int acceptorSocket;
    addrinfo hints, *servinfo, *p;
    sockaddr_storage connectorAddr;
    socklen_t sinSize;
    struct sigaction sa;
    int yes = 1;
    char address[INET6_ADDRSTRLEN];
    int rv;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my ip
    if ((rv = getaddrinfo(nullptr, PORT, &hints, &servinfo)) != 0) {
        std::cout << "getaddrinfo: " << gai_strerror(rv);
        throw ServerInitException{"getaddrinfo: " + std::string{gai_strerror(rv)}};
    }
    for (p = servinfo; p != nullptr; p = p->ai_next) {
        if ((acceptorSocket = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) { 
            std::cerr << "server: socket" << std::endl;
            continue;
        }
        if (setsockopt(acceptorSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            throw ServerInitException{"setsockopt"};
        }
        if (bind(acceptorSocket, p->ai_addr, p->ai_addrlen) == -1) { 
            close(acceptorSocket);
            std::cerr << "server: bind" << std::endl;
            continue; 
        }
        break;       
    }

    freeaddrinfo(servinfo);

    if (p == nullptr) {
        throw ServerInitException{"server: failed to bind"};
    }
    if (listen(acceptorSocket, PLAYERCOUNT) == -1) { 
        throw ServerInitException{"listen"};
    }

    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGCHLD, &sa, nullptr) == -1) {
        throw ServerInitException{"sigaction"};
    }

    std::cout << "server: waiting for 2 connections..." << std::endl;
    clientSockets.reserve(2);

    for (int i = 0; i < PLAYERCOUNT; ++i) {
        sinSize = sizeof(connectorAddr);
        int sockFd = accept(
            acceptorSocket, 
            reinterpret_cast<sockaddr *>(&connectorAddr),
            &sinSize
        );
        if (sockFd == -1) {
            for (int &socket: clientSockets) {
                closeSocket(socket);
            }
            throw ServerInitException{"Player " + std::to_string(i + 1) + " failed to connect"};
        }
        clientSockets.emplace_back(sockFd);
        inet_ntop(
            connectorAddr.ss_family, 
            get_in_addr(reinterpret_cast<sockaddr *>(&connectorAddr)),
            address,
            sizeof(address)
        );
        std::cout << "Player " << (i + 1) << " connected successfully from " << address << std::endl;
        std::cout << "socket file descriptor: " << sockFd << std::endl;
        send(sockFd, &i, sizeof(i), 0);
    }

    closeSocket(acceptorSocket);
}

// this method will run in GameController's serverThread
void Server::run() {
    // start the threads
    for (int i = 0; i < PLAYERCOUNT; ++i) {
        threads.emplace_back(std::thread{&Server::recvFromPlayer, this, std::ref(clientSockets[i])});
        // send(clientSockets[i], &i, sizeof(int), 0);
    }

    for (auto &thread: threads) if (thread.joinable()) thread.join();

    // close any sockets that hasn't been closed
    for (int &sockFd: clientSockets) closeSocket(sockFd);
}

void Server::recvFromPlayer(int &sockFd) {
    while (true) {
        Data data{};
        int numBytes = recv(sockFd, &data, sizeof(Data), 0);
        if (numBytes == 0) {
            std::cout << "player disconnected" << std::endl;
            controllerStream.setstate(std::ios::eofbit);
            break;
        }
        else if (numBytes == -1) {
            std::cout << "failed to receive message" << std::endl;
            controllerStream.setstate(std::ios::eofbit);
            break;
        }
        else if (turn != data.player_id) {
            sendMessage(sockFd, "Not your turn");
        }
        else {
            std::string message(data.msg, data.msg_len);
            controllerStream << message << std::endl;
        }
    }
    std::unique_lock<std::mutex> lock{mtx};
    for (auto &sockFd: clientSockets) closeSocket(sockFd);
}
