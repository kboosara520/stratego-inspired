#include "networking.h"

const char *ip = "127.0.0.1";
std::mutex mtx;

Data::Data(const std::string &message, int player_id): player_id{player_id}, msg_len{static_cast<int>(message.size())} {
    strncpy(msg, message.c_str(), sizeof(msg));
}

void closeSocket(int &sockFd) {
    std::lock_guard<std::mutex> lock{mtx};
    if (sockFd != -1) {
        int sockFdCopy = sockFd;
        close(sockFd);
        sockFd = -1;
        std::cout << "closed socket " << sockFdCopy << std::endl;
    }
}

void sendMessage(int sockfd, int cmd, const std::string &message, int player_id) {
    Data data{message, player_id};
    data.command = cmd;
    send(sockfd, &data, sizeof(Data), 0);
}

void *get_in_addr(sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((sockaddr_in *)sa)->sin_addr);
    }
    return &(((sockaddr_in6 *)sa)->sin6_addr);
}

void sigchld_handler(int s) {
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;
    while(waitpid(-1, nullptr, WNOHANG) > 0);
    errno = saved_errno;
}
