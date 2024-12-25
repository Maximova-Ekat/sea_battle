#ifndef STARTSTATE_H
#define STARTSTATE_H

#include "GameState.h"
#include "LoadState.h"
#include "CreateGameState.h"

class StartState : public GameState {
	Game* game;

public:

	StartState(Game* game);

	void doState() override;
};

#endif