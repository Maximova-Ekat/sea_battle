#ifndef LOADSTATE_H
#define LOADSTATE_H

#include "GameState.h"

class LoadState: public GameState{
public:
	Game* game;

public:

	LoadState(Game* game);

	void doState() override;
};

#endif