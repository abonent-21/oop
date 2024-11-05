#ifndef SHIP_GAME_GAME_H
#define SHIP_GAME_GAME_H
#include "GameField.h"
#include "AbilityManager.h"
#include <vector>

class Game {
public:
    Game();
    void run();

private:
    void initialize();
    void placeShips();
    void gameLoop();

    AbilityManager abilityManager_;
    GameField gameField_;
    int numShips_;
    std::vector<int> shipSizes_;
};
#endif //SHIP_GAME_GAME_H
