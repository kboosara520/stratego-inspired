#ifndef CLIENTINITEXCEPTION_H
#define CLIENTINITEXCEPTION_H

#include <iostream>
#include <exception>
#include <string>

class ClientInitException : public std::exception {
private:
    std::string message;

public:
    ClientInitException(const std::string& msg);

    const char *what() const noexcept override;
};

#endif