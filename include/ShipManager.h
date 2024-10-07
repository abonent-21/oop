#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H

#include <vector>
#include <unordered_map>
#include "Ship.h"

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2>& pair) const {
        auto hash1 = std::hash<T1>{}(pair.first);
        auto hash2 = std::hash<T2>{}(pair.second);
        return hash1 ^ hash2; // Объединение хешей с помощью XOR
    }
};

class ShipManager{
    public:
        struct ShipInfo
        {
            Ship ship;
            std::unordered_map<std::pair<int, int>, int, pair_hash> CoordAndSegment;
            
            ShipInfo(Ship&& ship, const std::vector<std::pair<int, int>>& positions);

            ShipInfo(ShipInfo&&) noexcept = default;
            ShipInfo& operator=(ShipInfo&&) noexcept = default;

        };


        ShipManager(int amount_of_ships, std::vector<int> size_of_ships);

        ShipManager(ShipManager&&) noexcept = default;
        ShipManager& operator=(ShipManager&&) noexcept = default;

        void addShip(Ship&& ship, const std::vector<std::pair<int, int>>& positions);
        void attackShip(int x, int y);
        bool allShipsDestroyed() const;
        bool isHit(int x, int y) const;
        bool isShipSegmentDamaged(int x, int y) const;
        bool isShipSegmentDestroyed(int x, int y) const;
        bool isShipSunkAt(int x, int y) const;

    private:
        int amount_of_ships_;
        std::vector<int> size_of_ships_;
        std::vector<ShipInfo> ships_;
};

#endif