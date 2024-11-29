#include "Game.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cstdlib>
#include "NoAbilitiesException.h"
#include "AttackOutOfBoundsException.h"
#include "ShipPlacementException.h"

Game::Game()
    : numShips_(0) {}


void Game::run() {
    std::string choice;
    std::cout << "Welcome to Battleship game!" << std::endl;

    while (true) {
        std::cout << "Do you want to (n)ew game or (l)oad game? ";
        std::cin >> choice;
        if (choice == "n" || choice == "l") {
            break; 
        } else {
            std::cout << "Invalid choice. Please enter 'n' for new game or 'l' to load game." << std::endl;
        }
    }

    if (choice == "l") {
        loadGame();
    } else if (choice == "n") {
        initialize();
        placeShips();
        placeEnemyShips();
    }
    gameLoop();
}

void Game::initialize() {
    std::cout << "Enter the number of ships: ";
    std::cin >> numShips_;
    
    for (int i = 0; i < numShips_; ++i) {
        int length;
        while (true) {
            std::cout << "Enter length of ship " << i + 1 << " (between 1 and 4): ";
            std::cin >> length;
            
            if (length >= 1 && length <= 4) {
                shipSizes_.push_back(length);
                break; 
            } else {
                std::cout << "Invalid length. Please enter a value between 1 and 4." << std::endl;
            }
        }
    }
    gameState_.getPlayerField().initializeShipManager(numShips_, shipSizes_);
    gameState_.setRoundNumber(1);
}

void Game::placeShips() {
    for (int i = 0; i < numShips_; ++i) {
        int x, y;
        char orientation;

        while (true) {
            gameState_.getPlayerField().print_field();
            std::cout << "Enter coordinates (x y) for ship of length " << shipSizes_[i] << ": ";
            std::cin >> x >> y;

            while (true) {
                std::cout << "Enter orientation (h - horizontal, v - vertical): ";
                std::cin >> orientation;

                if (orientation == 'h' || orientation == 'v') {
                    break; 
                } else {
                    std::cout << "Invalid orientation. Please enter 'h' for horizontal or 'v' for vertical." << std::endl;
                }
            }

            Ship::Orientation dir = (orientation == 'v') ? Ship::Orientation::Horizontal : Ship::Orientation::Vertical;
            Ship ship(shipSizes_[i], dir);

            try {
                gameState_.getPlayerField().placeShip(std::move(ship), x, y, dir);
                break; 
            } catch (const ShipPlacementException& e) {
                std::cout << e.what() << " Try again." << std::endl;
            }
        }
    }
}


void Game::placeEnemyShips() {
    GameField& enemyField = gameState_.getEnemyField();
    enemyField.initializeShipManager(numShips_, shipSizes_);
    for (int i = 0; i < numShips_; ++i) {
        bool placed = false;
        while (!placed) {
            int x = rand() % 10;
            int y = rand() % 10;
            Ship::Orientation orientation = (rand() % 2 == 0) ? Ship::Orientation::Horizontal : Ship::Orientation::Vertical;
            Ship ship(shipSizes_[i], orientation);
            try {
                enemyField.placeShip(std::move(ship), x, y, orientation);
                placed = true;
            } catch (const ShipPlacementException&) {

            }
        }
    }
}

void Game::gameLoop() {
    bool gameOver = false;
    while (!gameOver) {
        playerTurn();
        if (gameState_.getEnemyField().allShipsDestroyed()) {
            std::cout << "You win the round!" << std::endl;
            startNewRound();
            continue;
        }
        enemyTurn();
        if (gameState_.getPlayerField().allShipsDestroyed()) {
            std::cout << "You lost the game!" << std::endl;
            gameOver = true;
            break;
        }
    }
}

void Game::playerTurn() {
    bool turnOver = false;
    while (!turnOver) {
        std::string command;
        gameState_.getPlayerField().print_field();
        gameState_.getEnemyField().print_field();
        std::cout << "Your turn. Enter command ('attack x y', 'ability', 'save', 'load', 'exit'): ";
        std::cin >> command;
        if (command == "exit") {
            std::cout << "Game exited." << std::endl;
            exit(0);
        } else if (command == "save") {
            saveGame();
            continue;
        } else if (command == "load") {
            loadGame();
            continue;
        } else if (command == "ability") {
            if (!gameState_.getAbilityManager().hasAbilities()) {
                std::cout << "No abilities available." << std::endl;
                continue;
            }
            try {
                AbilityManager::AbilityType abilityType = gameState_.getAbilityManager().getNextAbilityType();
                if (abilityType == AbilityManager::AbilityType::Scanner) {
                    int x, y;
                    std::cout << "Enter coordinates of the top-left corner of 2x2 area to scan (x y): ";
                    std::cin >> x >> y;
                    bool found = gameState_.getEnemyField().scanArea(x, y);
                    if (found) {
                        std::cout << "Scanner detected a ship segment in the area." << std::endl;
                    } else {
                        std::cout << "No ship segments in the area." << std::endl;
                    }
                    gameState_.getAbilityManager().useAbility(gameState_.getEnemyField());
                } else if (abilityType == AbilityManager::AbilityType::DoubleDamage) {
                    gameState_.getAbilityManager().useAbility(gameState_.getEnemyField());
                    std::cout << "Double Damage ability activated for next attack." << std::endl;
                } else if (abilityType == AbilityManager::AbilityType::Bombardment) {
                    gameState_.getAbilityManager().useAbility(gameState_.getEnemyField());
                    std::cout << "Bombardment executed on enemy's ships." << std::endl;
                }
            } catch (const NoAbilitiesException& e) {
                std::cout << e.what() << std::endl;
            }
            if (gameState_.getEnemyField().allShipsDestroyed()) {
                std::cout << "You win the round!" << std::endl;
                startNewRound();
                return;
            }
            continue;
        } else if (command == "attack") {
            int x, y;
            std::cin >> x >> y;
            try {
                bool shipSunk = gameState_.getEnemyField().attackCell(x, y);
                if (shipSunk) {
                    gameState_.getAbilityManager().addRandomAbility();
                }
                if (gameState_.getEnemyField().allShipsDestroyed()) {
                    std::cout << "You win the round!" << std::endl;
                    startNewRound();
                    return;
                }
                turnOver = true;
            } catch (const AttackOutOfBoundsException& e) {
                std::cout << e.what() << std::endl;
                continue;
            }
        } else {
            std::cout << "Unknown command. Try again." << std::endl;
            continue;
        }
    }
}

void Game::enemyTurn() {
    std::cout << "Enemy's turn." << std::endl;
    int x, y;
    bool luckyStrike = rand() % 3;
    if (luckyStrike == 0) {
        do {
            x = rand() % 10;
            y = rand() % 10;
        } while (gameState_.getPlayerField().isCellEmpty(x, y));
    } else {
        x = rand() % 10;
        y = rand() % 10;
    }
    try {
        bool shipSunk = gameState_.getPlayerField().attackCell(x, y);
        std::cout << "Enemy attacked cell (" << x << ", " << y << ")." << std::endl;
        if (shipSunk) {
            std::cout << "Enemy sunk one of your ships!" << std::endl;
        }
    } catch (const AttackOutOfBoundsException& e) {
        std::cout<<e.what()<<std::endl;
    }
}

void Game::startNewRound() {
    std::cout<<"New Round is started"<<std::endl;
    int roundNumber = gameState_.getRoundNumber();
    gameState_.setRoundNumber(roundNumber + 1);
    std::cout<<"New round number is "<<gameState_.getRoundNumber()<< std::endl;
    GameField newEnemyField(10, 10);
    gameState_.setEnemyField(newEnemyField);
    placeEnemyShips();
}

void Game::saveGame() {
    std::string filename;
    std::cout << "Enter filename to save the game: ";
    std::cin >> filename;
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error opening file for saving." << std::endl;
        return;
    }
    outFile << gameState_;
    std::cout << "Game saved successfully." << std::endl;
}

void Game::loadGame() {
    std::string filename;
    std::cout << "Enter filename to load the game: ";
    std::cin >> filename;
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error opening file for loading." << std::endl;
        return;
    }
    inFile >> gameState_;
    std::cout << "Game loaded successfully." << std::endl;
}


//сделать обертку над файлом из которого читаем 
