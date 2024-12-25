#ifndef CREATEGAMESTATE_H
#define CREATEGAMESTATE_H

#include "GameState.h"
#include "CreatePlayer.h"
#include "PlayerUseAbilityState.h"

class CreateGameState : public GameState {
	Game* game;

public:

	CreateGameState(Game* game);

	void doState() override;
};

#endif
