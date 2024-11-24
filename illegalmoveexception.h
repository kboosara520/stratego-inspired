#include <iostream>
#include <string>
#include <stdexcept>

using namespace std; 

class IllegalMoveException : public exception {
private:
    string message;

public:
    IllegalMoveException(const string& msg): message(msg) {}

    const char* what() const noexcept override; 
};