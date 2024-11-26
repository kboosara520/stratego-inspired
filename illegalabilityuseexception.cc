#include "illegalabilityuseexception.h"

IllegalAbilityUseException::IllegalAbilityUseException(const std::string &msg): message{msg} {}

const char* IllegalAbilityUseException::what() const noexcept {
    return message.c_str();
}