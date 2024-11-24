#include "illegalmoveexception.h"

IllegalMoveException::IllegalMoveException(const string& msg): message(msg) {}

const char* IllegalMoveException::what() const noexcept {
    return message.c_str();
}
