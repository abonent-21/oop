#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H

#include <vector>
#include <unordered_map>
#include "Ship.h"

struct pair_hash {
    template<class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ (std::hash<T2>()(pair.second) << 1);
    }
};

class ShipManager {
public:
    struct ShipInfo {
        Ship ship;
        std::unordered_map<std::pair<int, int>, int, pair_hash> positionToSegmentIndex;

        ShipInfo(Ship &&ship, const std::vector<std::pair<int, int>> &positions);

    };

    ShipManager() = default;

    ShipManager(int num_of_ships, std::vector<int> size_of_ships);

    void addShip(Ship &&ship, const std::vector<std::pair<int, int>> &positions);

    void attackShip(int x, int y);

    bool allShipsDestroyed() const;

    bool isHit(int x, int y) const;

    bool isShipSegmentDamaged(int x, int y) const;

    bool isShipSegmentDestroyed(int x, int y) const;

    bool isShipSunkAt(int x, int y) const;

    void randomAttack();

private:
    int num_of_ships_;
    std::vector<int> size_of_ships_;
    std::vector<ShipInfo> ships_;
};

#endif
