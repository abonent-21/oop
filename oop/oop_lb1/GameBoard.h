#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Ship.h"
#include "ShipManager.h"
#include <vector>

enum class CellState {
    UNKNOWN,  // Неизвестно
    EMPTY,    // Пусто
    SHIP      // Корабль
};

class GameBoard {
public:
    static const int WIDTH = 10;
    static const int HEIGHT = 10;

    GameBoard();

    bool placeShip(Ship& ship, int x, int y, bool isHorizontal, ShipManager& manager);
    void attackCell(int x, int y, ShipManager& manager);
    void printBoard() const;

private:
    std::vector<std::vector<CellState>> grid;

    // Хранит информацию о расположении кораблей
    std::vector<std::pair<int, int>> shipPositions;  // Пары (shipIndex, segmentIndex)

    bool canPlaceShip(int x, int y, int length, bool isHorizontal) const;
};

#endif
