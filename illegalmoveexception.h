#ifndef ILLEGAL_MOVE_EXCEPTION_H
#define ILLEGAL_MOVE_EXCEPTION_H

#include <iostream>
#include <string>
#include <stdexcept> 

class IllegalMoveException : public std::exception {
private:
    std::string message;

public:
    IllegalMoveException(const std::string& msg);

    const char* what() const noexcept override; 
};

#endif
