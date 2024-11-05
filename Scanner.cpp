#include "Scanner.h"
#include "GameField.h"
#include <iostream>

bool Scanner::use(GameField &gameField, int x, int y) {
    if (!gameField.scanArea(x, y)) {
        return false;
    }
    return true;
}

std::string Scanner::getName() const {
    return "Сканер";
}