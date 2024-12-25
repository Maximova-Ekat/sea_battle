#ifndef SAVESTATE_H
#define SAVESTATE_H

#include "GameState.h"

class SaveState : public GameState {
	Game* game;

public:

	SaveState(Game* game);

	void doState() override;
};

#endif