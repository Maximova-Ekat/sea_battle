#ifndef CREATEPLAYER_H
#define CREATEPLAYER_H

#include "../include/Player.h"

class CreatePlayer {
	InputManager* input_manager;
	OutputManager<Output>* output_manager;
	Player* player;
	bool is_player;
	int width;
	int height;
	bool is_new;

	void createPlayer(bool is_hide = false);

	void setManager(bool is_hide = false);

	void infoManager(int number, std::vector <int> lengths);

	std::vector <int> countShip(int width, int height);

	void inputSizes();

	void inputAnswer(bool new_iteration = false);

	void inputCoordinates();

	void randomCoordinates();

	bool pseudoRandom(int x, int y, bool orientation, int number, bool is_player);

public:

	CreatePlayer(Player* player, bool is_player, int width = 0, int height = 0, bool is_new = false);

	~CreatePlayer() = default;
};

#endif