#include "GameBoard.h"
#include <iostream>
#include <stdexcept>

GameBoard::GameBoard()
    : grid(HEIGHT, std::vector<CellState>(WIDTH, CellState::UNKNOWN)) {}

bool GameBoard::canPlaceShip(int x, int y, int length, bool isHorizontal) const {
    if (isHorizontal) {
        if (x + length > WIDTH) return false;
        for (int i = 0; i < length; ++i) {
            if (grid[y][x + i] != CellState::UNKNOWN) return false;
        }
    } else {
        if (y + length > HEIGHT) return false;
        for (int i = 0; i < length; ++i) {
            if (grid[y + i][x] != CellState::UNKNOWN) return false;
        }
    }
    return true;
}

bool GameBoard::placeShip(Ship& ship, int x, int y, bool isHorizontal, ShipManager& manager) {
    if (!canPlaceShip(x, y, ship.getLength(), isHorizontal)) {
        return false; // Невозможно разместить корабль
    }

    // Запоминаем индекс нового корабля
    int shipIndex = manager.getShipCount(); // Индекс нового корабля

    for (int i = 0; i < ship.getLength(); ++i) {
        if (isHorizontal) {
            grid[y][x + i] = CellState::SHIP;
            shipPositions.emplace_back(shipIndex, i); // Запоминаем позицию сегмента
        } else {
            grid[y + i][x] = CellState::SHIP;
            shipPositions.emplace_back(shipIndex, i); // Запоминаем позицию сегмента
        }
    }

    manager.addShip(ship); // Добавляем корабль в менеджер после успешного размещения
    return true; // Корабль успешно размещен
}



void GameBoard::attackCell(int x, int y, ShipManager& manager) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        std::cout << "Координаты вне поля!" << std::endl;
        return;
    }

    if (grid[y][x] == CellState::SHIP) {
        // Поиск соответствующего корабля и сегмента
        for (size_t i = 0; i < shipPositions.size(); ++i) {
            auto [shipIndex, segmentIndex] = shipPositions[i];
            Ship& ship = manager.getShip(shipIndex);

            // Проверка, соответствует ли атакуемая клетка кораблю (с учётом ориентации)
            if ((ship.isHorizontal() && x == shipPositions[i].second && y == i) ||
                (!ship.isHorizontal() && y == shipPositions[i].second && x == i)) {

                SegmentState segmentState = ship.getSegmentState(segmentIndex);

                if (segmentState == SegmentState::INTACT) {
                    // Если сегмент целый, удар приводит его в поврежденное состояние
                    manager.updateShipState(shipIndex, segmentIndex);
                    //std::cout << "Сегмент поврежден!" << std::endl;

                } else if (segmentState == SegmentState::DAMAGED) {
                    // Если сегмент был повреждён, удар приводит к его уничтожению
                    manager.updateShipState(shipIndex, segmentIndex);
                    grid[y][x] = CellState::EMPTY; // Помечаем сегмент уничтоженным на поле
                    std::cout << "Корабль убит!" << std::endl;
                }

                return; // Заканчиваем обработку после удара
            }
        }
    } else if (grid[y][x] == CellState::EMPTY) {
        std::cout << "Мимо! Эта клетка уже была атакована." << std::endl;
    } else {
        std::cout << "Мимо!" << std::endl;
        grid[y][x] = CellState::EMPTY;
    }
}


void GameBoard::printBoard() const {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            switch (cell) {
                case CellState::UNKNOWN:
                    std::cout << ".";
                    break;
                case CellState::EMPTY:
                    std::cout << "o";
                    break;
                case CellState::SHIP:
                    std::cout << "S";
                    break;
            }
        }
        std::cout << std::endl;
    }
}