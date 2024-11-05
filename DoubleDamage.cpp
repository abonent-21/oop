#include "DoubleDamage.h"
#include "GameField.h"

bool DoubleDamage::use(GameField& gameField, int x, int y) {
    gameField.setDoubleDamageActive(true);
    gameField.attackCell(x, y);
}

std::string DoubleDamage::getName() const {
    return "Двойной урон";
}