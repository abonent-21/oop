#include "ShipManager.h"
#include <cstdlib>
#include <ctime>

ShipManager::ShipInfo::ShipInfo(Ship&& ship, const std::vector<std::pair<int, int>>& positions)
    : ship(std::move(ship)) {
    for (size_t i = 0; i < positions.size(); ++i) {
        positionToSegmentIndex[positions[i]] = static_cast<int>(i);
    }
}

ShipManager::ShipManager(int numShips, const std::vector<int>& shipSizes)
    : numShips_(numShips), shipSizes_(shipSizes) {
}

void ShipManager::addShip(Ship&& ship, const std::vector<std::pair<int, int>>& positions) {
    ships_.emplace_back(std::move(ship), positions);
}

void ShipManager::attackShip(int x, int y, int damage) {
    for (auto& shipInfo : ships_) {
        auto it = shipInfo.positionToSegmentIndex.find({x, y});
        if (it != shipInfo.positionToSegmentIndex.end()) {
            int segmentIndex = it->second;
            shipInfo.ship.takeDamage(segmentIndex, damage);
            return;
        }
    }
}

void ShipManager::randomAttack() {
    if (ships_.empty()) {
        return;
    }
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Собираем все неуничтоженные сегменты кораблей
    std::vector<std::pair<int, int>> targets;
    for (const auto& shipInfo : ships_) {
        if (!shipInfo.ship.isSunk()) {
            for (const auto& posPair : shipInfo.positionToSegmentIndex) {
                int segmentIndex = posPair.second;
                if (shipInfo.ship.getSegmentState(segmentIndex) != Ship::SegmentState::Destroyed) {
                    targets.push_back(posPair.first);
                }
            }
        }
    }

    if (targets.empty()) {
        return;
    }

    // Выбираем случайный сегмент
    auto target = targets[std::rand() % targets.size()];
    attackShip(target.first, target.second);
}

Ship::SegmentState ShipManager::getSegmentStateAt(int x, int y) const {
    for (const auto& shipInfo : ships_) {
        auto it = shipInfo.positionToSegmentIndex.find({x, y});
        if (it != shipInfo.positionToSegmentIndex.end()) {
            int segmentIndex = it->second;
            return shipInfo.ship.getSegmentState(segmentIndex);
        }
    }
    return Ship::SegmentState::Destroyed;
}

bool ShipManager::allShipsDestroyed() const {
    for (const auto& shipInfo : ships_) {
        if (!shipInfo.ship.isSunk()) {
            return false;
        }
    }
    return true;
}

bool ShipManager::isShipSegmentDamaged(int x, int y) const {
    return getSegmentStateAt(x, y) == Ship::SegmentState::Damaged;
}

bool ShipManager::isShipSegmentDestroyed(int x, int y) const {
    return getSegmentStateAt(x, y) == Ship::SegmentState::Destroyed;
}

bool ShipManager::isShipSunkAt(int x, int y) const {
    for (const auto& shipInfo : ships_) {
        if (shipInfo.positionToSegmentIndex.find({x, y}) != shipInfo.positionToSegmentIndex.end()) {
            return shipInfo.ship.isSunk();
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const ShipManager& manager) {
    os << manager.ships_.size() << std::endl;
    for (const auto& shipInfo : manager.ships_) {
        os << shipInfo.ship << std::endl;
        os << shipInfo.positionToSegmentIndex.size() << std::endl;
        for (const auto& pair : shipInfo.positionToSegmentIndex) {
            os << pair.first.first << ' ' << pair.first.second << ' ' << pair.second << std::endl;
        }
    }
    return os;
}

std::istream& operator>>(std::istream& is, ShipManager& manager) {
    size_t numShips;
    is >> numShips;
    manager.ships_.clear();
    manager.ships_.reserve(numShips);
    for (size_t i = 0; i < numShips; ++i) {
        Ship ship;
        is >> ship;
        size_t mapSize;
        is >> mapSize;
        std::unordered_map<std::pair<int, int>, int, PairHash> positionToSegmentIndex;
        for (size_t j = 0; j < mapSize; ++j) {
            int x, y, segmentIndex;
            is >> x >> y >> segmentIndex;
            positionToSegmentIndex[{x, y}] = segmentIndex;
        }
        ShipManager::ShipInfo shipInfo(std::move(ship), {});
        shipInfo.positionToSegmentIndex = std::move(positionToSegmentIndex);
        manager.ships_.push_back(std::move(shipInfo));
    }
    return is;
}
