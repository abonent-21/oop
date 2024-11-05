#ifndef BOMBARDMENT_H
#define BOMBARDMENT_H

#include "Ability.h"

class Bombardment : public Ability {
public:
    bool use(GameField &gameField, int x, int y) override;

    std::string getName() const override;
};

#endif // BOMBARDMENT_H