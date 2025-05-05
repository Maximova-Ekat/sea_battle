#ifndef BATTLESHIP_INTERACTIONMANAGER_H
#define BATTLESHIP_INTERACTIONMANAGER_H

#include "Field/Field.h"
#include "ShipsManager.h"
#include "AbilityManager.h"

class Game;

class InteractionManager {
private:
    Field* gamefield;
    ShipsManager* shipsManager;
    AbilityManager* abilityManager;
    bool isDoubleDamage;
    void addAbilityIfDestroyed(std::pair<int, int>coords);
    void setShips();
    friend class Game;
public:
    InteractionManager(int fieldHeight, int fieldWidth, int shipCount, int* shipSizes);
    Field* getField();
    ShipsManager* getShipsManager();
    AbilityManager* getAbilityManager();
    bool apply();
    void attack(std::pair<int, int> coords);
    void applyDoubleDamage();
    ~InteractionManager();
    void print();
    void load(Field* newF, ShipsManager* newS, AbilityManager* newA);
    void generateNewEnemy(int fieldHeight, int fieldWidth);
};


#endif //BATTLESHIP_INTERACTIONMANAGER_H
