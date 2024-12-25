#ifndef PLAYERUSEABILITYSTATE_H
#define PLAYERUSEABILITYSTATE_H

#include "GameState.h"
#include "PlayerWinState.h"
#include "BotMoveState.h"

class PlayerUseAbilityState : public GameState {
	Game* game;

public:

	PlayerUseAbilityState(Game* game);

	void doState() override;
};

#endif