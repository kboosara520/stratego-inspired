#include "serverinitexception.h"

ServerInitException::ServerInitException(const std::string& msg): message{msg} {}

const char *ServerInitException::what() const noexcept { return message.c_str(); }
