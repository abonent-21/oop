#include "GameBoard.h"
#include "Ship.h"
#include "ShipManager.h"
#include <iostream>

void printMenu() {
    std::cout << "\n=== Меню ===\n";
    std::cout << "1. Разместить корабль\n";
    std::cout << "2. Атаковать клетку\n";
    std::cout << "3. Показать игровое поле\n";
    std::cout << "4. Выйти\n";
    std::cout << "Выберите опцию: ";
}

void placeShip(GameBoard& board, ShipManager& manager) {
    int length, x, y;
    bool isHorizontal;

    std::cout << "Введите длину корабля (1-4): ";
    std::cin >> length;
    if (length < 1 || length > 4) {
        std::cout << "Неверная длина корабля. Длина должна быть от 1 до 4.\n";
        return;
    }

    std::cout << "Введите координаты x и y для размещения (например, 0 0): ";
    std::cin >> x >> y;

    std::cout << "Горизонтальное размещение? (1 - да, 0 - нет): ";
    std::cin >> isHorizontal;

    Ship ship(length, isHorizontal);
    if (board.placeShip(ship, x, y, isHorizontal, manager)) {
        std::cout << "Корабль успешно размещен.\n";
    } else {
        std::cout << "Не удалось разместить корабль на указанных координатах.\n";
    }
}

void attackCell(GameBoard& board, ShipManager& manager) {
    int x, y;
    std::cout << "Введите координаты атаки x и y (например, 0 0): ";
    std::cin >> x >> y;
    board.attackCell(x, y, manager);
}

int main() {
    GameBoard board;
    ShipManager manager;

    while (true) {
        printMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                placeShip(board, manager);
                break;
            case 2:
                attackCell(board, manager);
                break;
            case 3:
                board.printBoard();
                break;
            case 4:
                std::cout << "Выход из игры. Спасибо за игру! Возвращайтесь снова!\n";
                return 0;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }

    return 0;
}
