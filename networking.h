#ifndef NETWORKING_H
#define NETWORKING_H

#define PORT "3060"
#define BOARD 10
#define MESSAGE 11

#include <arpa/inet.h> 
#include <errno.h> 
#include <netdb.h> 
#include <signal.h>
#include <sys/socket.h> 
#include <unistd.h> 

#include <atomic>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>

#define MAXMSGLEN 244

extern const char *ip;
struct Data {
    int player_id;
    int command;
    char msg[MAXMSGLEN];
    int msg_len;
    Data() {}
    Data(const std::string &message, int player_id = 0);
};

inline void sendMessage(int sockfd, int cmd, const std::string &message, int player_id = -1) {
    Data data{message, player_id};
    data.command = cmd;
    send(sockfd, &data, sizeof(Data), 0);
}

inline void *get_in_addr(sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((sockaddr_in *)sa)->sin_addr);
    }
    return &(((sockaddr_in6 *)sa)->sin6_addr);
}

inline void closeSocket(int &sockFd) {
    if (sockFd != -1) {
        std::cout << "closing socket " << sockFd << std::endl;
        close(sockFd);
        sockFd = -1;
    }
}

inline void sigchld_handler(int s) {
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;
    while(waitpid(-1, nullptr, WNOHANG) > 0);
    errno = saved_errno;
}

#endif
