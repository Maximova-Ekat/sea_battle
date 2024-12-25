#include "StartState.h"
#include "Game.h"

void StartState::doState() {
	game->changeState(new CreateGameState(game));
}

StartState::StartState(Game* game) : game(game) {};