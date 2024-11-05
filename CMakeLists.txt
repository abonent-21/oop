cmake_minimum_required(VERSION 3.29)
project(ship_game)

set(CMAKE_CXX_STANDARD 14)

add_executable(ship_game
        Ability.h
        AbilityManager.h
        Bombing.h
        DoubleDamage.h
        GameField.cpp
        GameField.h
        main.cpp
        Scanner.h
        Ship.cpp
        Ship.h
        ShipManager.cpp
        ShipManager.h
        Scanner.cpp
        DoubleDamage.cpp
        Game.h
        Game.cpp)
