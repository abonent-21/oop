#include "Game.h"
#include <iostream>
#include <string>
#include <limits>
#include "NoAbilitiesException.h"
#include "AttackOutOfBoundsException.h"
#include "ShipPlacementException.h"

Game::Game()
        : abilityManager_(),
          gameField_(10, 10, abilityManager_),
          numShips_(0) {}

void Game::initialize() {
    std::cout << "Добро пожаловать в игру 'Морской бой'!" << std::endl;

    while (true) {
        std::cout << "Введите количество кораблей: ";
        std::cin >> numShips_;
        if (std::cin.fail() || numShips_ <= 0) {
            std::cout << "Некорректный ввод. Количество кораблей должно быть положительным целым числом!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    for (int i = 0; i < numShips_; ++i) {
        int length;
        while (true) {
            std::cout << "Введите длину корабля " << i + 1 << ": ";
            std::cin >> length;
            if (std::cin.fail() || length <= 0 || length > 4) {
                std::cout << "Некорректный ввод. Длина корабля должна быть от 1 до 4!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                shipSizes_.push_back(length);
                break;
            }
        }
    }

    gameField_.initializeShipManager(numShips_, shipSizes_);
}

void Game::placeShips() {
    for (int i = 0; i < numShips_; ++i) {
        int x, y;
        char orientation;
        while (true) {
            std::cout << "Введите координаты (x y) для корабля длины " << shipSizes_[i] << ": ";
            std::cin >> x >> y;
            if (std::cin.fail() || x < 0 || x >= 10 || y < 0 || y >= 10) {
                std::cout << "Некорректные координаты. Координаты должны быть целыми числами в диапазоне (0-9)!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            std::cout << "Введите ориентацию (h - горизонтально, v - вертикально): ";
            std::cin >> orientation;
            if (orientation != 'h' && orientation != 'v') {
                std::cout << "Некорректная ориентация. Должно быть 'h' для горизонтально или 'v' для вертикально!" << std::endl;
                continue;
            }

            try {
                Ship::Orientation dir = (orientation == 'h') ? Ship::Orientation::Horizontal : Ship::Orientation::Vertical;
                Ship ship(shipSizes_[i], dir);
                gameField_.placeShip(std::move(ship), x, y, dir);
                std::cout << "Корабль успешно размещен." << std::endl;
                break;
            } catch (const ShipPlacementException& e) {
                std::cout << e.what() << " Попробуйте снова." << std::endl;
            }
        }
    }
}

void Game::gameLoop() {
    bool gameOver = false;
    std::string command;

    while (!gameOver) {
        std::cout << "Введите команду (x y для атаки, 'ability' для применения способности или 'exit' для выхода): ";
        std::cin >> command;

        if (command == "exit") {
            std::cout << "Игра завершена." << std::endl;
            break;
        }

        if (command == "ability") {
            try {
                abilityManager_.useAbility(gameField_);
            } catch (const NoAbilitiesException& e) {
                std::cout << e.what() << std::endl;
            }
            // Проверяем окончание игры после применения способности
            if (gameField_.allShipsDestroyed()) {
                std::cout << "Все корабли уничтожены! Игра окончена." << std::endl;
                gameOver = true;
            }
            continue;
        }

        int x, y;
        try {
            x = std::stoi(command);
            if (!(std::cin >> y)) {
                throw std::invalid_argument("Некорректный ввод");
            }

            try {
                gameField_.attackCell(x, y);

                // Проверяем окончание игры после атаки
                if (gameField_.allShipsDestroyed()) {
                    std::cout << "Все корабли уничтожены! Игра окончена." << std::endl;
                    gameOver = true;
                }
            } catch (const AttackOutOfBoundsException& e) {
                std::cout << e.what() << std::endl;
            }
        } catch (std::exception&) {
            std::cout << "Некорректный ввод. Введите числовые значения координат или 'exit' для выхода." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }
}

void Game::run() {
    initialize();
    placeShips();
    gameLoop();
}