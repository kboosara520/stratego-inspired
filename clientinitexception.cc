#include "clientinitexception.h"

ClientInitException::ClientInitException(const std::string &msg): message{msg} {}

const char *ClientInitException::what() const noexcept {
    return message.c_str();
}
