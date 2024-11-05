#include "Ship.h"
#include "ShipManager.h"
#include "GameField.h"
#include <iostream>
#include <string>
#include <limits>

int main() {
    std::cout << "Welcome to the Battleship game!" << std::endl;

    int numShips;
    while (true) {
        std::cout << "Enter the number of ships: ";
        std::cin >> numShips;
        if (std::cin.fail() || numShips <= 0) {
            std::cout << "Invalid input. The number of ships must be a positive integer!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    std::vector<int> shipSizes;
    for (int i = 0; i < numShips; ++i) {
        int length;
        while (true) {
            std::cout << "Enter the length of ship " << i + 1 << ": ";
            std::cin >> length;
            if (std::cin.fail() || length <= 0 || length > 4) {
                std::cout << "Invalid input. The length of the ship must be between 1 and 4!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                shipSizes.push_back(length);
                break;
            }
        }
    }

    ShipManager shipManager;
    GameField gameField(10, 10, shipManager);
    bool gameOver = false;
    gameField.print_field();

    for (int i = 0; i < numShips; ++i) {
        int x, y;
        char orientation;
        while (true) {
            std::cout << "Enter orientation (h - horizontal, v - vertical): ";
            std::cin >> orientation;
            if (orientation != 'h' && orientation != 'v') {
                std::cout << "Invalid orientation. Must be 'h' for horizontal or 'v' for vertical!" << std::endl;
                continue;
            }

            std::cout << "Enter coordinates (x y) for ship of length " << shipSizes[i] << ": ";
            std::cin >> x >> y;
            if (std::cin.fail() || x < 0 || x >= 10 || y < 0 || y >= 10) {
                std::cout << "Invalid coordinates. Coordinates must be integers within the range (0-9)!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            Ship::Orientation dir = (orientation == 'h') ? Ship::Orientation::Horizontal : Ship::Orientation::Vertical;
            Ship ship(shipSizes[i], dir);
            if (gameField.placeShip(std::move(ship), x, y, dir)) {
                std::cout << "Ship placed successfully." << std::endl;
                gameField.print_field();
                break;
            } else {
                std::cout << "Error: Unable to place the ship at these coordinates. Try again." << std::endl;
            }
        }
    }

    std::string command;
    while (!gameOver) {
        std::cout << "Enter command (x y to attack or 'exit' to quit): ";
        std::cin >> command;

        if (command == "exit") {
            std::cout << "Game exited." << std::endl;
            break;
        }

        int x, y;
        try {
            x = std::stoi(command);
            if (!(std::cin >> y)) {
                throw std::invalid_argument("Invalid input");
            }
        } catch (std::exception&) {
            std::cout << "Invalid input. Please enter numeric values for coordinates or 'exit' to quit." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (x < 0 || x >= 10 || y < 0 || y >= 10) {
            std::cout << "Coordinates must be within the range (0-9)!" << std::endl;
            continue;
        }

        gameField.attackCell(x, y);
        gameField.print_field();
        
        if (shipManager.allShipsDestroyed()) {
            std::cout << "All ships are destroyed! Game over." << std::endl;
            gameOver = true;
        }
    }

    return 0;
}
