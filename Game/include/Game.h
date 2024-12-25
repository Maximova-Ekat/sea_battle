#ifndef GAME_H
#define GAME_H

#include <typeinfo>
#include <fstream>
#include "../include/Player.h"
#include "../InputManager/include/InputManager.h"
#include "../OutputManager/include/OutputManager.h"
#include "GameState.h"
#include "StartState.h"
#include "CreateGameState.h"
#include "BotMoveState.h"
#include "BotWinState.h"
#include "PlayerAttackState.h"
#include "PlayerUseAbilityState.h"
#include "PlayerWinState.h"
#include "LoadState.h"
#include "SaveState.h"

class Game {

	Player* player;
	Player* bot;
	InputManager* input_manager;
	Output out{ std::cout };
	OutputManager<Output>* output_manager;
	GameState* next_state;

	void stringToState(std::string str);

public:

	Game(InputManager* input_manager);

	void doState();

	void createGame();

	void quit();
	
	void saveGame();

	void loadGame();

	void attack();

	void useAbility();

	Player* getPlayer(bool is_player = true);

	void changeState(GameState* new_state); 

	json to_json() const;

	void from_json(const json& j);

	void changeNextState(GameState* new_state);

	GameState* getNextState() const;

	OutputManager<Output>* getOutputManager();

	friend std::ofstream& operator<<(std::ofstream& out, Game* game);

	friend std::ifstream& operator>>(std::ifstream& in, Game* game);

	~Game();
};

std::ofstream& operator<<(std::ofstream& out, Game* game);

std::ifstream& operator>>(std::ifstream& in, Game* game);

#endif