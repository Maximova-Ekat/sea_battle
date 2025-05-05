#include "AbilityManager.h"
#include "abilities/DoubleDamage.h"
#include "abilities/Scanner.h"
#include "abilities/Bombardment.h"
#include <random>
#include <iostream>


AbilityManager::AbilityManager(void* manager) {
    allAbilities.push_back(new DoubleDamage(manager));
    allAbilities.push_back(new Scanner(manager));
    allAbilities.push_back(new Bombardment(manager));
    std::shuffle(allAbilities.begin(), allAbilities.end(), std::mt19937(std::random_device()()));
    for (size_t i = 0; i < allAbilities.size(); ++i) {
        abilities.push(allAbilities[i]);
    }
}

std::queue<Ability*> AbilityManager::getAbilities() {
    return abilities;
}

bool AbilityManager::applyAbility() {
    if (!abilities.empty()) {
        Ability* ability = abilities.front();
        abilities.pop();
        return ability->apply();
    }
}

void AbilityManager::addRandomAbility() {
    if (!allAbilities.empty()) {
        int randomIndex = rand() % allAbilities.size();
        abilities.push(allAbilities[randomIndex]);
    }
}

void AbilityManager::printAbilities() {
    std::queue<Ability*> tempQueue = abilities;
    std::string result = "Способности в очереди: ";
    while (!tempQueue.empty()) {
        Ability* ability = tempQueue.front();
        tempQueue.pop();
        result += ability->getName();
        if (!tempQueue.empty()) {
            result += ", ";
        }
    }
    std::cout << result << std::endl;

}

AbilityManager::~AbilityManager() {
    while (!abilities.empty()) {
        abilities.pop();
    }

    for (Ability *ability: allAbilities) {
        delete ability;
    }
}

json AbilityManager::save_to_json(){
    json j;
    j["abilities"] = json::array();
    std::queue<Ability*> tempQueue = abilities;

    while (!tempQueue.empty()) {
        Ability* ability = tempQueue.front();
        tempQueue.pop();
        j["abilities"].push_back(ability->getName());
    }

    return j;
}

void AbilityManager::from_json(json j, void* manager) {
    while (!abilities.empty()) {
        abilities.pop();
    }

    for (const auto& abilityType : j["abilities"]) {
        if (abilityType == "DoubleDamage") {
            abilities.push(new DoubleDamage(manager));
        } else if (abilityType == "Scanner") {
            abilities.push(new Scanner(manager));
        } else if (abilityType == "Bombardment") {
            abilities.push(new Bombardment(manager));
        }
    }
}