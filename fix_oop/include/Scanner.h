#ifndef SCANNER_H
#define SCANNER_H

#include "Ability.h"

class Scanner : public Ability {
public:
    void use(GameField& gameField) override;
    std::unique_ptr<Ability> clone() const override;
};

#endif 
