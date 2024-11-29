#include "Bombardment.h"
#include "GameField.h"

void Bombardment::use(GameField& gameField) {
    gameField.randomBombardment();
}

std::unique_ptr<Ability> Bombardment::clone() const {
    return std::make_unique<Bombardment>(*this);
}
