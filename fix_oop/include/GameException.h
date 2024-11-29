#ifndef GAMEEXCEPTION_H
#define GAMEEXCEPTION_H

#include <exception>
#include <string>

class GameException : public std::exception {
public:
    explicit GameException(const std::string& message);
    const char* what() const noexcept override;

private:
    std::string message_;
};

#endif 
