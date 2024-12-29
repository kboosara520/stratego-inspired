#include <arpa/inet.h> 
#include <errno.h> 
#include <netdb.h> 
#include <signal.h>
#include <sys/socket.h> 
#include <unistd.h> 

#include <iostream>
#include <string>
#include <thread>

const int MAXMSGLEN = 244;

struct Data {
    int player_id;
    int command;
    char msg[MAXMSGLEN];
    int msg_len;
    Data() {}
    Data(const std::string &message, int player_id = 0): player_id{player_id}, msg_len{static_cast<int>(message.size())} {
        strncpy(msg, message.c_str(), sizeof(msg));
    }
};

void send_message(int sockfd, const std::string &message, int player_id = -1) {
    Data data{message, player_id};
    send(sockfd, &data, sizeof(Data), 0);
}
