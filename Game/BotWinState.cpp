#include "BotWinState.h"
#include "Game.h"

void BotWinState::doState() {
	game->getPlayer()->getOutputManager()->printMessage("Вы проиграли..\nНовая игра\n");
	
	game->changeNextState(new CreateGameState(game));
	//switch StartState
}

BotWinState::BotWinState(Game* game) : game(game) {};