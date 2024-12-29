#include "networking.h"

const char *ip = "127.0.0.1";

Data::Data(const std::string &message, int player_id): player_id{player_id}, msg_len{static_cast<int>(message.size())} {
    strncpy(msg, message.c_str(), sizeof(msg));
}
