#ifndef ABILITYMANAGER_H
#define ABILITYMANAGER_H

#include <queue>
#include <memory>
#include "Ability.h"

class AbilityManager {
public:
    AbilityManager();

    void addRandomAbility();

    void useAbility(GameField &gameField);

    bool hasAbilities() const;

private:
    void generateRandomAbility();

    std::queue<std::unique_ptr<Ability>> abilities_;
};

#endif // ABILITYMANAGER_H