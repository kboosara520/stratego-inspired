#ifndef ILLEGAL_ABILITY_USE_EXCEPTION_H
#define ILLEGAL_ABILITY_USE_EXCEPTION_H

#include <iostream>
#include <string>
#include <stdexcept>

class IllegalAbilityUseException: public std::exception {
    std::string message;
  public:
    IllegalAbilityUseException(const std::string &msg);
    const char *what() const noexcept override;
};

#endif
