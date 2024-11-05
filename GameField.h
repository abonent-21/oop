#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <vector>
#include "ShipManager.h"
#include "AbilityManager.h"

class GameField {
public:
    enum class CellStatus {Unknown, Empty, Ship, Hit, Occupied};

    GameField(int width, int height, ShipManager &shipManager, AbilityManager &abilityManager);

    //Конструктор копирования
    GameField(const GameField &other, AbilityManager &abilityManager);

    // Конструктор перемещенния
    GameField(GameField &&other, AbilityManager &abilityManager) noexcept;

    //деструктор
    ~GameField() = default;

    void print_field();
    bool placeShip(Ship&& ship, int x, int y, Ship::Orientation orientation);
    bool attackCell(int x, int y);
    void set_cell_status(CellStatus cell_status, int x, int y);
    GameField& operator=(GameField&& other) noexcept;
    bool allShipsDestroyed() const;
    void initializeShipManager(int numShips, const std::vector<int>& shipSizes);

    void setDoubleDamageActive(bool active);
    bool scanArea(int x, int y);
    void randomBombardment();

private:
    int width_, height_;
    std::vector<std::vector<CellStatus>> grid_;
    ShipManager& shipManager_;
    AbilityManager& abilityManager_;
    bool doubleDamageActive_ = false;
};

#endif
