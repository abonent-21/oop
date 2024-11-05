#include "ShipManager.h"
#include <iostream>


ShipManager::ShipManager() {}

void ShipManager::addShip(const Ship& ship) {
    ships.push_back(ship);
}

void ShipManager::updateShipState(int shipIndex, int segmentIndex) {
    if (shipIndex < 0 || shipIndex >= ships.size()) {
        throw std::out_of_range("Индекс корабля вне диапазона");
    }

    Ship& ship = ships[shipIndex];
    SegmentState previousState = ship.getSegmentState(segmentIndex);

    // Если сегмент уже уничтожен, не нужно его повторно атаковать
    if (previousState == SegmentState::DESTROYED) {
        std::cout << "Эта клетка уже была атакована." << std::endl;
        return;
    }

    // Наносим удар по сегменту
    ship.hitSegment(segmentIndex);

    // Проверим состояние сегмента после удара
    SegmentState currentState = ship.getSegmentState(segmentIndex);

    // Логика вывода сообщений
    if (previousState == SegmentState::INTACT && currentState == SegmentState::DAMAGED) {
        std::cout << "Сегмент поврежден!" << std::endl;
        std::cout << "Корабль ранен!" << std::endl;
    } else if (previousState == SegmentState::DAMAGED && currentState == SegmentState::DESTROYED) {
        std::cout << "Сегмент уничтожен!" << std::endl;

        // Проверяем, уничтожен ли весь корабль
        if (ship.isSunk()) {
            std::cout << "Корабль убит!" << std::endl;
        }
    }
}

int ShipManager::getShipCount() const {
    return ships.size();
}

Ship& ShipManager::getShip(int shipIndex) {
    if (shipIndex < 0 || shipIndex >= ships.size()) {
        throw std::out_of_range("Индекс корабля вне диапазона");
    }
    return ships[shipIndex];
}
