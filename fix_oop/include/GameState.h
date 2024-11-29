#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameField.h"
#include "AbilityManager.h"
#include <iostream>

class GameState {
public:
    GameState();

    const GameField& getPlayerField() const;
    GameField& getPlayerField();
    void setPlayerField(const GameField& field);

    const GameField& getEnemyField() const;
    GameField& getEnemyField();
    void setEnemyField(const GameField& field);

    const AbilityManager& getAbilityManager() const;
    AbilityManager& getAbilityManager();
    void setAbilityManager(const AbilityManager& abilityManager);

    int getRoundNumber() const;
    void setRoundNumber(int round);

    friend std::ostream& operator<<(std::ostream& os, const GameState& state);
    friend std::istream& operator>>(std::istream& is, GameState& state);

private:
    GameField playerField_;
    GameField enemyField_;
    AbilityManager abilityManager_;
    int roundNumber_;
};

#endif 