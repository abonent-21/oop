#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <vector>
#include "ShipManager.h"

class GameField {
public:
    enum class CellStatus {Unknown, Empty, Ship, Hit, Occupied};

    GameField(int width, int height, ShipManager& shipManager);

    //Конструктор копирования
    GameField(const GameField& other);

    // Конструктор перемещенния
    GameField(GameField&& other) noexcept;

    //деструктор
    ~GameField() = default;

    void print_field();
    bool placeShip(Ship&& ship, int x, int y, Ship::Orientation orientation);
    bool attackCell(int x, int y);
    void set_cell_status(CellStatus cell_status, int x, int y);
    GameField& operator=(GameField&& other) noexcept;

private:
    int width_, height_;
    std::vector<std::vector<CellStatus>> grid_;
    ShipManager& shipManager_;
};

#endif
