

#ifndef BATTLESHIP_ABILITYMANAGER_H
#define BATTLESHIP_ABILITYMANAGER_H

#include "abilities/Ability.h"
#include "Field/Field.h"
#include "ShipsManager.h"
#include <vector>
#include <queue>
#include <cstdlib>
#include <algorithm>

class AbilityManager {
private:
    std::queue<Ability*> abilities;
    std::vector<Ability*> allAbilities; // Все доступные способности
public:
    AbilityManager(void* manager);
    std::queue<Ability*> getAbilities();
    bool applyAbility();
    void addRandomAbility();
    ~AbilityManager();
    void printAbilities();
    json save_to_json();
    void from_json(json j, void* manager);
};

#endif //BATTLESHIP_ABILITYMANAGER_H
