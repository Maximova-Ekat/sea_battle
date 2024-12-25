#include "PlayerUseAbilityState.h"
#include "Game.h"

void PlayerUseAbilityState::doState() {
	Player* player = game->getPlayer();
	Player* bot = game->getPlayer(false);
	bool value = player->playerMove(true);
	OutputManager<Output>* output_manager = player->getOutputManager();
	output_manager->showField(player->getField(), bot->getField());
	if (value == true) {
		game->changeState(new PlayerWinState(game));
		//return true;   switch PlayerWinState
	}
	else {
		game->changeNextState(new PlayerAttackState(game));
	}
	//playerattack
}

PlayerUseAbilityState::PlayerUseAbilityState(Game* game) : game(game) {};