#ifndef ATTACKOUTOFBOUNDSEXCEPTION_H
#define ATTACKOUTOFBOUNDSEXCEPTION_H

#include "GameException.h"

class AttackOutOfBoundsException : public GameException {
public:
    AttackOutOfBoundsException();
};

#endif 
