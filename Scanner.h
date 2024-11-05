#ifndef SCANNER_H
#define SCANNER_H

#include "Ability.h"

class Scanner : public Ability {
public:
    bool use(GameField& gameField, int x, int y) override;
    std::string getName() const override; // Добавили эту строку
};

#endif // SCANNER_H