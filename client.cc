#include "client.h"

Client::Client() {
    addrinfo hints, *servinfo, *p;
    int rv;
    char address[INET6_ADDRSTRLEN];
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(ip, PORT, &hints, &servinfo)) != 0) {
        throw ClientInitException{"getaddrinfo: " + std::string{gai_strerror(rv)}};
    }
    for (p = servinfo; p != nullptr; p = p->ai_next) {
        if ((sockFd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            std::cerr << "client: socket" << std::endl;
            continue;
        }
        if (connect(sockFd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockFd);
            std::cerr << "client: connect" << std::endl;
            continue;
        }
        break;
    }
    if (!p) {
        throw ClientInitException{"client: failed to connect"};
    }

    inet_ntop(
        p->ai_family,
        get_in_addr(reinterpret_cast<sockaddr *>(p->ai_addr)),
        address,
        sizeof(address)
    );
    std::cout << "client: connected to server, address: " << address << std::endl;
    freeaddrinfo(servinfo);
    gameRunning = true;
}

void Client::run() {
    std::thread recvThread{&Client::recvFromServer, this};
    std::string message;
    while (getline(std::cin, message)) {
        if (!gameRunning || message == "exit") break;
        else if (message.size() == 0) continue;
        else if (message.size() > MAXMSGLEN) {
            std::cout << "length of message cannot exceed " << MAXMSGLEN << " chars" << std::endl;
            continue;
        }
        else if (message[0] == '/') {
            message.erase(message.begin());
            if (message.size() == 0) {
                std::cout << "cannot send an empty message" << std::endl;
            }
            else {
                message = "Player " + std::to_string(playerId + 1) + " says: " + message;
                sendMessage(sockFd, CHAT, message, playerId);
            }
        }
        else {
            sendMessage(sockFd, MESSAGE, message, playerId);
        }
    }
    closeSocket(sockFd);
    if (recvThread.joinable()) {
        recvThread.join();
        std::cout << "receiving thread joined" << std::endl;
    }
    else {
        std::cout << "receiving thread is not joinable" << std::endl;
    }
}

void Client::recvFromServer() {
    while (true) {
        Data data{};
        int numBytes = recv(sockFd, &data, sizeof(Data), 0);
        if (numBytes == 0) {
            std::cout << "disconnected from the server" << std::endl;
            break;
        }
        else if (numBytes < 0) {
            if (errno != EBADF) {
                std::cout << "Something went wrong, errno: " << errno << std::endl;
            }
            break;
        }
        else if (numBytes == 1 && data.player_id == ping) {
            continue; // just a ping from the server
        }
        else if (data.command == ENDGAME) {
            std::cout << "The game has ended" << std::endl;
            break;
        }
        else if (playerId < 0) {
            playerId = data.player_id;
            std::cout << "You are Player " << (playerId + 1) << std::endl;
        }
        else {
            std::string message(data.msg, data.msg_len);
            std::cout << message << std::endl;
        }
    }
    closeSocket(sockFd);
    gameRunning = false;
}
