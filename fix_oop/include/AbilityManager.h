#ifndef ABILITYMANAGER_H
#define ABILITYMANAGER_H

#include <vector>
#include <memory>
#include "Ability.h"

class AbilityManager {
public:
    enum class AbilityType { DoubleDamage, Scanner, Bombardment };

    AbilityManager();
    AbilityManager(const AbilityManager& other);
    AbilityManager& operator=(const AbilityManager& other);

    void addRandomAbility();
    void useAbility(GameField& gameField);
    bool hasAbilities() const;
    AbilityType getNextAbilityType() const;

    friend std::ostream& operator<<(std::ostream& os, const AbilityManager& manager);
    friend std::istream& operator>>(std::istream& is, AbilityManager& manager);

private:
    void generateRandomAbility();
    std::vector<std::pair<AbilityType, std::unique_ptr<Ability>>> abilities_;
};

#endif 
