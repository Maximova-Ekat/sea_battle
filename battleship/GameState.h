#ifndef GAME_STATE
#define GAME_STATE

#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"
#include "InteractionManager.h"

using json = nlohmann::json;
using namespace std;

class GameState {
private:
    string filename;
    json save_game;
    Field* myField;
    ShipsManager* myShips;
    Field* enemyF;
    ShipsManager* enemyS;
    AbilityManager* myAbilities;
    InteractionManager* manager;
    ofstream outfile;
    ifstream infile;

public:
    GameState(string filename);
    void saving(Field* myField, ShipsManager* myShips, InteractionManager* manager);
    void loading(Field* myField, ShipsManager* myShips, InteractionManager* manager);
    bool is_file_written() const {
        std::ifstream file(filename);
        return file.peek() != std::ifstream::traits_type::eof();
    }
    friend ostream& operator<<(ostream& os, const GameState& state);
    friend istream& operator>>(istream& is, GameState& state);
};

#endif