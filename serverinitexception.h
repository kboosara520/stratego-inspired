#ifndef SERVERINITEXCEPTION_H
#define SERVERINITEXCPETION_H

#include <iostream>
#include <exception>
#include <string>

class ServerInitException : public std::exception {
private:
    std::string message;

public:
    ServerInitException(const std::string& msg);

    const char *what() const noexcept override;
};

#endif
