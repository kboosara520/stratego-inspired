#ifndef NETWORKING_H
#define NETWORKING_H

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
#include <future>

#define PORT "3060"
#define CHAT 10
#define MESSAGE 11
#define ENDGAME 99
#define MAXMSGLEN 300

extern const char *ip;
extern std::mutex mtx;

struct Data {
    int player_id;
    int command;
    char msg[MAXMSGLEN];
    int msg_len;
    Data() {}
    Data(const std::string &message, int player_id = 0);
};

void closeSocket(int &sockFd);
void sendMessage(int sockfd, int cmd, const std::string &message, int player_id = -1);
void *get_in_addr(sockaddr *sa);
void sigchld_handler(int s);

#endif
