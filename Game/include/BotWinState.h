#ifndef BOTWINSTATE_H
#define BOTWINSTATE_H

#include "GameState.h"
#include "StartState.h"

class BotWinState : public GameState {
	Game* game;

public:

	BotWinState(Game* game);

	void doState() override;
};

#endif