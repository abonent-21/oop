#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <vector>
#include "ShipManager.h"

class AbilityManager; // Forward declaration

class GameField {
public:
    enum class CellStatus {Unknown, Empty, Ship};

    GameField(int width = 10, int height = 10);

    GameField(const GameField& other);
    GameField& operator=(const GameField& other);

    GameField(GameField&& other) noexcept;
    GameField& operator=(GameField&& other) noexcept;

    void placeShip(Ship&& ship, int x, int y, Ship::Orientation orientation);
    bool attackCell(int x, int y);
    bool allShipsDestroyed() const;
    void initializeShipManager(int numShips, const std::vector<int>& shipSizes);
    void set_cell_status(CellStatus cell_status, int x, int y);

    void setDoubleDamageActive(bool active);
    bool scanArea(int x, int y) const;
    void randomBombardment();
    bool wasCellAttacked(int x, int y) const;
    bool isCellEmpty(int x, int y);
    void print_field();

    friend std::ostream& operator<<(std::ostream& os, const GameField& field);
    friend std::istream& operator>>(std::istream& is, GameField& field);

private:
    int width_, height_;
    std::vector<std::vector<CellStatus>> grid_;
    ShipManager shipManager_;
    bool doubleDamageActive_;
};

#endif 
