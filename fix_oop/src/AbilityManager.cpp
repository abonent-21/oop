#include "AbilityManager.h"
#include "DoubleDamage.h"
#include "Scanner.h"
#include "Bombardment.h"
#include "NoAbilitiesException.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

AbilityManager::AbilityManager() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::vector<AbilityType> initialAbilities = {
        AbilityType::DoubleDamage,
        AbilityType::Scanner,
        AbilityType::Bombardment
    };

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(initialAbilities.begin(), initialAbilities.end(), g);

    for (auto& type : initialAbilities) {
        switch (type) {
            case AbilityType::DoubleDamage:
                abilities_.emplace_back(type, std::make_unique<DoubleDamage>());
                break;
            case AbilityType::Scanner:
                abilities_.emplace_back(type, std::make_unique<Scanner>());
                break;
            case AbilityType::Bombardment:
                abilities_.emplace_back(type, std::make_unique<Bombardment>());
                break;
        }
    }
}

AbilityManager::AbilityManager(const AbilityManager& other) {
    for (const auto& abilityPair : other.abilities_) {
        abilities_.emplace_back(abilityPair.first, abilityPair.second->clone());
    }
}

AbilityManager& AbilityManager::operator=(const AbilityManager& other) {
    if (this != &other) {
        abilities_.clear();
        for (const auto& abilityPair : other.abilities_) {
            abilities_.emplace_back(abilityPair.first, abilityPair.second->clone());
        }
    }
    return *this;
}

void AbilityManager::generateRandomAbility() {
    int abilityType = std::rand() % 3;
    AbilityType type = static_cast<AbilityType>(abilityType);
    std::unique_ptr<Ability> newAbility;

    switch (type) {
        case AbilityType::DoubleDamage:
            newAbility = std::make_unique<DoubleDamage>();
            break;
        case AbilityType::Scanner:
            newAbility = std::make_unique<Scanner>();
            break;
        case AbilityType::Bombardment:
            newAbility = std::make_unique<Bombardment>();
            break;
    }
    abilities_.emplace_back(type, std::move(newAbility));
}

void AbilityManager::addRandomAbility() {
    generateRandomAbility();
}

void AbilityManager::useAbility(GameField& gameField) {
    if (abilities_.empty()) {
        throw NoAbilitiesException();
    }

    abilities_.front().second->use(gameField);
    abilities_.erase(abilities_.begin());
}

bool AbilityManager::hasAbilities() const {
    return !abilities_.empty();
}

AbilityManager::AbilityType AbilityManager::getNextAbilityType() const {
    if (abilities_.empty()) {
        throw NoAbilitiesException();
    }
    return abilities_.front().first;
}

std::ostream& operator<<(std::ostream& os, const AbilityManager& manager) {
    os << manager.abilities_.size() << std::endl;
    for (const auto& abilityPair : manager.abilities_) {
        os << static_cast<int>(abilityPair.first) << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, AbilityManager& manager) {
    size_t numAbilities;
    is >> numAbilities;
    manager.abilities_.clear();
    for (size_t i = 0; i < numAbilities; ++i) {
        int abilityTypeInt;
        is >> abilityTypeInt;
        AbilityManager::AbilityType type = static_cast<AbilityManager::AbilityType>(abilityTypeInt);
        std::unique_ptr<Ability> ability;
        switch (type) {
            case AbilityManager::AbilityType::DoubleDamage:
                ability = std::make_unique<DoubleDamage>();
                break;
            case AbilityManager::AbilityType::Scanner:
                ability = std::make_unique<Scanner>();
                break;
            case AbilityManager::AbilityType::Bombardment:
                ability = std::make_unique<Bombardment>();
                break;
        }
        manager.abilities_.emplace_back(type, std::move(ability));
    }
    return is;
}
