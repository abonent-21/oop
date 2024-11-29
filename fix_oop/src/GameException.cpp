#include "GameException.h"

GameException::GameException(const std::string& message)
    : message_(message) {}

const char* GameException::what() const noexcept {
    return message_.c_str();
}
