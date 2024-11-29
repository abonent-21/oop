#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H

#include <vector>
#include <unordered_map>
#include "Ship.h"
#include "PairHash.h"
#include <iostream>

class ShipManager {
public:
    struct ShipInfo {
        Ship ship;
        std::unordered_map<std::pair<int, int>, int, PairHash> positionToSegmentIndex;

        ShipInfo(Ship&& ship, const std::vector<std::pair<int, int>>& positions);

        ShipInfo(const ShipInfo&) = default;
        ShipInfo& operator=(const ShipInfo&) = default;

        ShipInfo(ShipInfo&&) noexcept = default;
        ShipInfo& operator=(ShipInfo&&) noexcept = default;
    };

    ShipManager() = default;
    ShipManager(int numShips, const std::vector<int>& shipSizes);

    void addShip(Ship&& ship, const std::vector<std::pair<int, int>>& positions);
    void attackShip(int x, int y, int damage = 1);
    bool allShipsDestroyed() const;
    Ship::SegmentState getSegmentStateAt(int x, int y) const;
    bool isShipSegmentDamaged(int x, int y) const;
    bool isShipSegmentDestroyed(int x, int y) const;
    bool isShipSunkAt(int x, int y) const;
    void randomAttack();

    friend std::ostream& operator<<(std::ostream& os, const ShipManager& manager);
    friend std::istream& operator>>(std::istream& is, ShipManager& manager);

private:
    std::vector<ShipInfo> ships_;
    int numShips_ = 0;
    std::vector<int> shipSizes_;
};

#endif 
