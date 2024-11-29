#include "GameField.h"
#include "ShipPlacementException.h"
#include "AttackOutOfBoundsException.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

GameField::GameField(int width, int height)
    : width_(width), height_(height),
      grid_(width, std::vector<CellStatus>(height, CellStatus::Unknown)),
      shipManager_(),
      doubleDamageActive_(false) {}

GameField::GameField(const GameField& other)
    : width_(other.width_), height_(other.height_),
      grid_(other.grid_), shipManager_(other.shipManager_),
      doubleDamageActive_(other.doubleDamageActive_) {}

GameField& GameField::operator=(const GameField& other) {
    if (this != &other) {
        width_ = other.width_;
        height_ = other.height_;
        grid_ = other.grid_;
        shipManager_ = other.shipManager_;
        doubleDamageActive_ = other.doubleDamageActive_;
    }
    return *this;
}

GameField::GameField(GameField&& other) noexcept
    : width_(other.width_), height_(other.height_),
      grid_(std::move(other.grid_)), shipManager_(std::move(other.shipManager_)),
      doubleDamageActive_(other.doubleDamageActive_) {
    other.width_ = 0;
    other.height_ = 0;
    other.doubleDamageActive_ = false;
}

GameField& GameField::operator=(GameField&& other) noexcept {
    if (this != &other) {
        width_ = other.width_;
        height_ = other.height_;
        grid_ = std::move(other.grid_);
        shipManager_ = std::move(other.shipManager_);
        doubleDamageActive_ = other.doubleDamageActive_;

        other.width_ = 0;
        other.height_ = 0;
        other.doubleDamageActive_ = false;
    }
    return *this;
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
        Ship::SegmentState segmentState = shipManager_.getSegmentStateAt(y, 0);
        if (grid_[y][0] == CellStatus::Ship && segmentState == Ship::SegmentState::Damaged){
            std::cout << y << '|' << "*" << "|";
        }
        else if (grid_[y][0] == CellStatus::Ship && segmentState == Ship::SegmentState::Destroyed){
            std::cout << y << '|' << "#" << "|";
        }
        else if (grid_[y][0] == CellStatus::Ship){
            std::cout << y << '|' << "X" << "|";
        }
        else{
            std::cout << y << '|' << " " << "|";
        }
        for (int x = 1; x < width_; x++){
            Ship::SegmentState segmentState1 = shipManager_.getSegmentStateAt(y, x);
            if (grid_[y][x] == CellStatus::Ship && segmentState1 == Ship::SegmentState::Damaged){
                std::cout << "*" << "|";
            }
            else if (grid_[y][x] == CellStatus::Ship && segmentState1 == Ship::SegmentState::Destroyed){
                std::cout << "#" << "|";
            }
            else if (grid_[y][x] == CellStatus::Ship){
                std::cout << "X" << "|";
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

void GameField::set_cell_status(CellStatus cell_status, int x, int y){
    grid_[x][y] = cell_status;
}

void GameField::placeShip(Ship&& ship, int x, int y, Ship::Orientation orientation) {
    std::vector<std::pair<int, int>> positions;
    int dx = (orientation == Ship::Orientation::Horizontal) ? 1 : 0;
    int dy = (orientation == Ship::Orientation::Vertical) ? 1 : 0;

    for (int i = 0; i < ship.getLength(); ++i) {
        int nx = x + dx * i;
        int ny = y + dy * i;

        if (nx < 0 || nx >= width_ || ny < 0 || ny >= height_) {
            throw ShipPlacementException();
        }

        if (grid_[nx][ny] != CellStatus::Unknown) {
            throw ShipPlacementException();
        }

        positions.emplace_back(nx, ny);
    }

    for (const auto& pos : positions) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int nx = pos.first + i;
                int ny = pos.second + j;
                if (nx >= 0 && nx < width_ && ny >= 0 && ny < height_) {
                    if (grid_[nx][ny] == CellStatus::Ship && !(nx == pos.first && ny == pos.second)) {
                        throw ShipPlacementException();
                    }
                    }
                }
            }
        }

    for (const auto& pos : positions) {
        set_cell_status(CellStatus::Ship, pos.first, pos.second);
    }

    shipManager_.addShip(std::move(ship), positions);
}

bool GameField::attackCell(int x, int y) {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        throw AttackOutOfBoundsException();
    }

    CellStatus& cell = grid_[x][y];

    if (cell == CellStatus::Ship) {
        Ship::SegmentState segmentState = shipManager_.getSegmentStateAt(x, y);

        if (segmentState == Ship::SegmentState::Destroyed) {
            std::cout << "This cell was already attacked." << std::endl;
            return false;
        }

        int damage = doubleDamageActive_ ? 2 : 1;
        doubleDamageActive_ = false;

        shipManager_.attackShip(x, y, damage);
        segmentState = shipManager_.getSegmentStateAt(x, y);

        if (segmentState == Ship::SegmentState::Damaged) {
            std::cout << "Segment damaged!" << std::endl;
        } else if (segmentState == Ship::SegmentState::Destroyed) {
            std::cout << "Segment destroyed!" << std::endl;
            if (shipManager_.isShipSunkAt(x, y)) {
                std::cout << "Ship sunk!" << std::endl;
                return true;
            }
        }

    } else if (cell == CellStatus::Unknown) {
        std::cout << "Miss!" << std::endl;
        cell = CellStatus::Empty;
    } else {
        std::cout << "This cell was already attacked." << std::endl;
    }
    return false;
}

void GameField::setDoubleDamageActive(bool active) {
    doubleDamageActive_ = active;
}

bool GameField::scanArea(int x, int y) const {
    if (x < 0 || x >= width_ - 1 || y < 0 || y >= height_ - 1) {
        return false;
    }
    for (int i = x; i < x + 2; ++i) {
        for (int j = y; j < y + 2; ++j) {
            if (grid_[i][j] == CellStatus::Ship) {
                return true;
            }
        }
    }
    return false;
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

bool GameField::isCellEmpty(int x, int y) {
    return !(grid_[x][y] == CellStatus::Ship);
}

bool GameField::wasCellAttacked(int x, int y) const {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        return true;
    }
    CellStatus cell = grid_[x][y];
    return cell == CellStatus::Empty || shipManager_.isShipSegmentDamaged(x, y) || shipManager_.isShipSegmentDestroyed(x, y);
}

std::ostream& operator<<(std::ostream& os, const GameField& field) {
    os << field.width_ << ' ' << field.height_ << std::endl;
    for (int i = 0; i < field.width_; ++i) {
        for (int j = 0; j < field.height_; ++j) {
            os << static_cast<int>(field.grid_[i][j]) << ' ';
        }
        os << std::endl;
    }
    os << field.doubleDamageActive_ << std::endl;
    os << field.shipManager_ << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, GameField& field) {
    is >> field.width_ >> field.height_;
    field.grid_.resize(field.width_, std::vector<GameField::CellStatus>(field.height_));
    int cellStatusInt;
    for (int i = 0; i < field.width_; ++i) {
        for (int j = 0; j < field.height_; ++j) {
            is >> cellStatusInt;
            field.grid_[i][j] = static_cast<GameField::CellStatus>(cellStatusInt);
        }
    }
    is >> field.doubleDamageActive_;
    is >> field.shipManager_;
    return is;
}
