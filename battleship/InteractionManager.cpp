#include "InteractionManager.h"

#include <iostream>


InteractionManager::InteractionManager(int fieldHeight, int fieldWidth, int shipCount, int* shipSizes) {
    gamefield = new Field(fieldHeight, fieldWidth);
    shipsManager = new ShipsManager(shipCount, shipSizes);
    abilityManager = new AbilityManager(this);
    isDoubleDamage = false;
}

Field* InteractionManager::getField() {
    return gamefield;
}

ShipsManager* InteractionManager::getShipsManager() {
    return shipsManager;
}

AbilityManager* InteractionManager::getAbilityManager() {
    return abilityManager;
}

void InteractionManager::addAbilityIfDestroyed(std::pair<int, int>coords) {
    if (gamefield->getCells()[coords.first][coords.second]->getTrueState() == FieldCellState::Ship
        && gamefield->getCells()[coords.first][coords.second]->getShip()->isDestroyed()){
        abilityManager->addRandomAbility();
    }
}

void InteractionManager::attack(std::pair<int, int> coords) {
    if(isDoubleDamage) {
        gamefield->dealDoubleDamage(coords);
        isDoubleDamage = false;
    } else {
        gamefield->attack(coords);
    }
    addAbilityIfDestroyed(coords);
}

bool InteractionManager::apply() {
    return abilityManager->applyAbility();
}

InteractionManager::~InteractionManager() {
    delete gamefield;
    delete shipsManager;
    delete abilityManager;
}

void InteractionManager::print() {
    shipsManager->print();
}

void InteractionManager::applyDoubleDamage() {
    isDoubleDamage = true;
}

void InteractionManager::load(Field* newF, ShipsManager* newS, AbilityManager* newA){
    delete gamefield;
    delete shipsManager;
    delete abilityManager;
    gamefield = newF;
    shipsManager = newS;
    abilityManager = newA;
}

void InteractionManager::generateNewEnemy(int fieldHeight, int fieldWidth) {
    auto newF = new Field(fieldHeight, fieldWidth);
    *gamefield = *newF;
    shipsManager->genNewShips();
}

