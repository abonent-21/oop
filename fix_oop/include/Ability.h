#ifndef ABILITY_H
#define ABILITY_H

#include "GameField.h"
#include <memory>

class Ability {
public:
    virtual ~Ability() = default;
    virtual void use(GameField& gameField) = 0;
    virtual std::unique_ptr<Ability> clone() const = 0;
};

#endif 