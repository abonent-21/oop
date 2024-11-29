#ifndef BOMBARDMENT_H
#define BOMBARDMENT_H

#include "Ability.h"

class Bombardment : public Ability {
public:
    void use(GameField& gameField) override;
    std::unique_ptr<Ability> clone() const override;
};

#endif 
