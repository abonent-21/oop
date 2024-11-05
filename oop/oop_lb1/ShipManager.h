#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H

#include "Ship.h"
#include <vector>

class ShipManager {
public:
    ShipManager();

    void addShip(const Ship& ship);
    void updateShipState(int shipIndex, int segmentIndex);
    Ship& getShip(int shipIndex);
    //const std::vector<Ship>& getShips() const;  // Добавить этот метод
    int getShipCount() const;

private:
    std::vector<Ship> ships;
};

#endif
