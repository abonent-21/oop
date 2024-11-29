#include "AttackOutOfBoundsException.h"

AttackOutOfBoundsException::AttackOutOfBoundsException()
    : GameException("Attack coordinates are outside the field boundaries.") {}
