#include "DoubleDamage.h"
#include "GameField.h"

void DoubleDamage::use(GameField& gameField) {
    gameField.setDoubleDamageActive(true);
}

std::unique_ptr<Ability> DoubleDamage::clone() const {
    return std::make_unique<DoubleDamage>(*this);
}
