#include "GameState.h"

GameState::GameState()
    : playerField_(10, 10), enemyField_(10, 10), roundNumber_(1) {}

const GameField& GameState::getPlayerField() const {
    return playerField_;
}

GameField& GameState::getPlayerField() {
    return playerField_;
}

void GameState::setPlayerField(const GameField& field) {
    playerField_ = field;
}

const GameField& GameState::getEnemyField() const {
    return enemyField_;
}

GameField& GameState::getEnemyField() {
    return enemyField_;
}

void GameState::setEnemyField(const GameField& field) {
    enemyField_ = field;
}

const AbilityManager& GameState::getAbilityManager() const {
    return abilityManager_;
}

AbilityManager& GameState::getAbilityManager() {
    return abilityManager_;
}

void GameState::setAbilityManager(const AbilityManager& abilityManager) {
    abilityManager_ = abilityManager;
}

int GameState::getRoundNumber() const {
    return roundNumber_;
}

void GameState::setRoundNumber(int round) {
    roundNumber_ = round;
}

std::ostream& operator<<(std::ostream& os, const GameState& state) {
    os << state.roundNumber_ << std::endl;
    os << state.playerField_ << std::endl;
    os << state.enemyField_ << std::endl;
    os << state.abilityManager_ << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, GameState& state) {
    is >> state.roundNumber_;
    is >> state.playerField_;
    is >> state.enemyField_;
    is >> state.abilityManager_;
    return is;
}
