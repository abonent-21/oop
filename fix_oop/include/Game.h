#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include <vector>

class Game {
public:
    Game();
    void run();

private:
    void initialize();
    void placeShips();
    void placeEnemyShips();
    void gameLoop();
    void playerTurn();
    void enemyTurn();
    void startNewRound();
    void saveGame();
    void loadGame();

    GameState gameState_;
    int numShips_;
    std::vector<int> shipSizes_;
};

#endif 
