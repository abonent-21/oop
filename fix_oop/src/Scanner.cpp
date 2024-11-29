#include "Scanner.h"
#include "GameField.h"

void Scanner::use(GameField& gameField) {
    (void)gameField; 
    
}

std::unique_ptr<Ability> Scanner::clone() const {
    return std::make_unique<Scanner>(*this);
}
