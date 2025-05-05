//
// Created by vanec on 29.11.2024.
//

#include "InteractionManager.h"
#include "GameState.h"
#include "FieldPrinter.h"
#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <random>

#ifndef BATTLESHIP_GAME_H
#define BATTLESHIP_GAME_H


class Game {
    bool isStarted = false;
    bool isExit = false;
    InteractionManager* manager;
    Field* myField;
    ShipsManager* myShips;
    GameState* state;
    void rewrite();
    void compAttack();
public:
    Game();
    void exitGame();
    void saveGame();
    void loadGame();
    void attack(std::pair<int, int> coords);
    bool useAbility();
    void play();
    ~Game();
    std::pair<int, int> setField();
    int getValidInput(const string &prompt, int minValue, int maxValue);
    std::pair<int, int*> setupShipsManager();
    void placeUserShips();
    void placeEnemyShips();
    void userTurn();
    void startNewGame();
    void turn(bool isUserTurn);
    void stopOrContinue(bool userShipsAreDestroyed, bool enemyShipsAreDestroyed);
};


#endif //BATTLESHIP_GAME_H
