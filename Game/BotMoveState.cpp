#include "BotMoveState.h"
#include "Game.h"

void BotMoveState::doState() {
	Player* player = game->getPlayer();
	Player* bot = game->getPlayer(false);
	bool value = bot->playerMove();
	OutputManager<Output>* output_manager = player->getOutputManager();
	output_manager->showField(player->getField(), bot->getField());

	if (value == true) {
		game->changeState(new BotWinState(game));
		//return true;   switch BotWinState
	}
	else {
		game->changeNextState(new PlayerUseAbilityState(game));
	}
}

BotMoveState::BotMoveState(Game* game) : game(game) {};