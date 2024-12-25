#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../include/Player.h"
#include "Exception.h"

class Game;
class GameState {
public:
	virtual void doState() = 0;
};

#endif