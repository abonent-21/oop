#include "GameField.h"

#include <iostream>

GameField::GameField(int width, int height, ShipManager &shipManager, AbilityManager &abilityManager)
    : width_(width), height_(height),
      grid_(width, std::vector<CellStatus>(height, CellStatus::Unknown)),
      shipManager_(shipManager), abilityManager_(abilityManager) {}

GameField::GameField(const GameField &other, AbilityManager &abilityManager)
        : width_(other.width_), height_(other.height_),
          grid_(other.grid_), shipManager_(other.shipManager_), abilityManager_(abilityManager) {}

GameField::GameField(GameField &&other, AbilityManager &abilityManager) noexcept
        : width_(other.width_), height_(other.height_),
          grid_(std::move(other.grid_)), shipManager_(other.shipManager_), abilityManager_(abilityManager) {
        other.width_ = 0;
        other.height_ = 0;
    }

GameField& GameField::operator=(GameField&& other) noexcept {
    if (this != &other) {
        width_ = other.width_;
        height_ = other.height_;
        grid_ = std::move(other.grid_);
        shipManager_ = std::move(other.shipManager_);

        other.width_ = 0;
        other.height_ = 0;
    }
    return *this;
}

void GameField::set_cell_status(CellStatus cell_status, int x, int y){
    grid_[x][y] = cell_status;
}

void GameField::print_field(){
    std::cout << "  ";
    for (int i = 0; i < width_; i++){
        std::cout << i << " ";
    }
    std::cout << "\n";
    for (int i = 0; i <= width_; i++){
        std::cout << "--";
    }
    std::cout << "\n";
    for (int y = 0; y < height_; y++){
        if (grid_[y][0] == CellStatus::Ship){
            std::cout << y << '|' << "X" << "|";
        }
        else if (grid_[y][0] == CellStatus::Hit){
            std::cout << y << '|' << "*" << "|";
        }
        else{
            std::cout << y << '|' << " " << "|";
        }
        for (int x = 1; x < width_; x++){
            if (grid_[y][x] == CellStatus::Ship){
                std::cout << "X" << "|";
            }
            else if (grid_[y][x] == CellStatus::Hit){
                std::cout << "*" << "|";
            }
            else{
                std::cout << " " << "|";
            }
        }
        std::cout << "\n";
        for (int i = 0; i <= width_; i++){
            std::cout << "--";
        }
        std::cout << "\n";
    }
}

bool GameField::placeShip(Ship&& ship, int x, int y, Ship::Orientation orientation) {
    std::vector<std::pair<int, int>> positions;

    if (orientation == Ship::Orientation::Vertical) {
        if (x + ship.getLength() > width_) return false;
        if (x - 1 >= 0){
                GameField::set_cell_status(CellStatus::Occupied, x - 1, y);
            }
        if (y + 1 < width_ && x - 1 >= 0){
                GameField::set_cell_status(CellStatus::Occupied, x - 1, y + 1);
            }
        if (y - 1 >= 0 && x - 1 >= 0){
                GameField::set_cell_status(CellStatus::Occupied, x - 1, y - 1);
            }
        for (int i = 0; i < ship.getLength(); ++i){
            if (grid_[x + i][y] != CellStatus::Unknown){
                return false;
            }
            if (y + 1 < width_){
                GameField::set_cell_status(CellStatus::Occupied, x + i, y + 1);
            }
            if (y - 1 >= 0){
                GameField::set_cell_status(CellStatus::Occupied, x + i, y - 1);
            }
            positions.emplace_back(x + i, y);
        }
        if (x + ship.getLength() < width_){
                GameField::set_cell_status(CellStatus::Occupied, x + ship.getLength() , y);
            }
        if (y + 1 < height_ && x + ship.getLength()  < width_){
                GameField::set_cell_status(CellStatus::Occupied, x + ship.getLength(), y + 1);
            }
        if (y - 1 >= 0 && x + ship.getLength() < width_){
                GameField::set_cell_status(CellStatus::Occupied, x + ship.getLength(), y - 1);
            }

    } else {
        if (y + ship.getLength() > height_) return false;
        if (y - 1 >= 0){
                GameField::set_cell_status(CellStatus::Occupied, x, y - 1);
            }
        if (x + 1 < height_ && y - 1 >= 0){
                GameField::set_cell_status(CellStatus::Occupied, x + 1, y - 1);
            }
        if (y - 1 >= 0 && x - 1 >= 0){
                GameField::set_cell_status(CellStatus::Occupied, x - 1, y - 1);
            }
        for (int i = 0; i < ship.getLength(); ++i) {
            if (grid_[x][y + i] != CellStatus::Unknown){
                return false;
            }
            if (x + 1 < height_){
                GameField::set_cell_status(CellStatus::Occupied, x + 1, y + i);
            }
            if (x - 1 >= 0){
                GameField::set_cell_status(CellStatus::Occupied, x - 1, y + i);
            }
            positions.emplace_back(x, y + i);
        }
        if (y + ship.getLength() < width_){
                GameField::set_cell_status(CellStatus::Occupied, x, y + ship.getLength());
            }
        if (x + 1 < height_ && y + ship.getLength()  < width_){
                GameField::set_cell_status(CellStatus::Occupied, x + 1, y + ship.getLength());
            }
        if (x - 1 >= 0 && y + ship.getLength() < width_){
                GameField::set_cell_status(CellStatus::Occupied, x - 1, y + ship.getLength());
            }
    }

    for (const auto& pos : positions) {
        grid_[pos.first][pos.second] = CellStatus::Ship;
    }

    shipManager_.addShip(std::move(ship), positions);
    return true;
}

bool GameField::attackCell(int x, int y) {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        std::cout << "Invalid coordinates." << std::endl;
        return false;
    }

    CellStatus& cell = grid_[x][y];

    // Check if the cell contains a ship
    if (cell == CellStatus::Ship || cell == CellStatus::Hit) {
        bool segmentDestroyed = shipManager_.isShipSegmentDestroyed(x, y);
        bool segmentDamaged = shipManager_.isShipSegmentDamaged(x, y);

        if (segmentDestroyed) {
            std::cout << "This segment is already destroyed." << std::endl;
            return false;
        }

        if (doubleDamageActive_){
            shipManager_.attackShip(x, y);
            shipManager_.attackShip(x, y);
            doubleDamageActive_ = false;
        }
        else{
            shipManager_.attackShip(x, y);
        }

        if (!segmentDamaged) {
            std::cout << "Hit!" << std::endl;
        } else {
            std::cout << "Segment destroyed!" << std::endl;
            if (shipManager_.isShipSunkAt(x, y)) {
                std::cout << "You sunk a ship!" << std::endl;
            }
        }


        cell = CellStatus::Hit;

        return true;
    }

    if (cell == CellStatus::Unknown || cell == CellStatus::Occupied) {
        std::cout << "Miss!" << std::endl;
        cell = CellStatus::Empty;
        return false;
    }

    if (cell == CellStatus::Empty) {
        std::cout << "This cell was already attacked." << std::endl;
        return false;
    }

    return false;
}

void GameField::setDoubleDamageActive(bool active) {
    doubleDamageActive_ = active;
}

bool GameField::scanArea(int x, int y) {
    if (x < 0 || x >= width_ - 1 || y < 0 || y >= height_ - 1) {
        return false;
    }
    for (int i = x; i < x + 2; ++i) {
        for (int j = y; j < y + 2; ++j) {
            if (grid_[i][j] == CellStatus::Ship || grid_[i][j] == CellStatus::Hit) {
                std::cout << "Сканер обнаружил сегмент корабля в области." << std::endl;
                return true;
            }
        }
    }
    std::cout << "В области нет сегментов кораблей." << std::endl;
    return true;
}

void GameField::randomBombardment() {
    shipManager_.randomAttack();
}

bool GameField::allShipsDestroyed() const {
    return shipManager_.allShipsDestroyed();
}

void GameField::initializeShipManager(int numShips, const std::vector<int>& shipSizes) {
    shipManager_ = ShipManager(numShips, shipSizes);
}