#ifndef SHIP_GAME_DOUBLEDAMAGE_H
#define SHIP_GAME_DOUBLEDAMAGE_H

#include "Ability.h"

class DoubleDamage : public Ability {
public:
    bool use(GameField &gameField, int x, int y) override;

    std::string getName() const override;
};

#endif //SHIP_GAME_DOUBLEDAMAGE_H
