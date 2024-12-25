#ifndef PLAYERATTACKSTATE_H
#define PLAYERATTACKSTATE_H

#include "GameState.h"
#include "PlayerWinState.h"
#include "BotMoveState.h"

class PlayerAttackState : public GameState {
	Game* game;

public:

	PlayerAttackState(Game* game);

	void doState() override;
};

#endif