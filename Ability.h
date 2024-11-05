#ifndef ABILITY_H
#define ABILITY_H

#include <string>

class GameField;

class Ability {
public:
    virtual ~Ability() = default;

    virtual bool use(GameField &gameField, int x, int y) = 0;

    virtual std::string getName() const = 0; // Добавили эту строку
};

#endif // ABILITY_H