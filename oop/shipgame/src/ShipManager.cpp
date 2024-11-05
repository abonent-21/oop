#include "ShipManager.h"
#include <cstddef>  // Для std::size_t

ShipManager::ShipManager(int num_of_ships, std::vector<int> size_of_ships){
    num_of_ships_ = num_of_ships;
    size_of_ships_ = size_of_ships;
}

ShipManager::ShipInfo::ShipInfo(Ship&& ship, const std::vector<std::pair<int, int>>& positions)
    : ship(std::move(ship)) {
    for (std::size_t i = 0; i < positions.size(); ++i) {  // Используем std::size_t для индекса
        positionToSegmentIndex[positions[i]] = static_cast<int>(i);
    }
}

void ShipManager::addShip(Ship&& ship, const std::vector<std::pair<int, int>>& positions) {
    ships_.emplace_back(std::move(ship), positions);
}

void ShipManager::attackShip(int x, int y) {
    for (auto& shipInfo : ships_) {
        auto it = shipInfo.positionToSegmentIndex.find({x, y});
        if (it != shipInfo.positionToSegmentIndex.end()) {
            int segmentIndex = it->second;
            shipInfo.ship.takeDamage(segmentIndex);
            return;
        }
    }
}

bool ShipManager::isShipSunkAt(int x, int y) const {
    for (const auto& shipInfo : ships_) {
        if (shipInfo.positionToSegmentIndex.find({x, y}) != shipInfo.positionToSegmentIndex.end()) {
            return shipInfo.ship.isSunk();
        }
    }
    return false;
}

bool ShipManager::allShipsDestroyed() const {
    for (const auto& shipInfo : ships_) {
        if (!shipInfo.ship.isSunk()) {
            return false;
        }
    }
    return true;
}

bool ShipManager::isHit(int x, int y) const {
    for (const auto& shipInfo : ships_) {
        if (shipInfo.positionToSegmentIndex.find({x, y}) != shipInfo.positionToSegmentIndex.end()) {
            return true;
        }
    }
    return false;
}

bool ShipManager::isShipSegmentDamaged(int x, int y) const {
    for (const auto& shipInfo : ships_) {
        auto it = shipInfo.positionToSegmentIndex.find({x, y});
        if (it != shipInfo.positionToSegmentIndex.end()) {
            int segmentIndex = it->second;
            return shipInfo.ship.getSegmentState(segmentIndex) == Ship::SegmentState::Damaged;
        }
    }
    return false;
}

bool ShipManager::isShipSegmentDestroyed(int x, int y) const {
    for (const auto& shipInfo : ships_) {
        auto it = shipInfo.positionToSegmentIndex.find({x, y});
        if (it != shipInfo.positionToSegmentIndex.end()) {
            int segmentIndex = it->second;
            return shipInfo.ship.getSegmentState(segmentIndex) == Ship::SegmentState::Destroyed;
        }
    }
    return false;
}