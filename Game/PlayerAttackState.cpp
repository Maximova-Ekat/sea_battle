#include "PlayerAttackState.h"
#include "Game.h"

void PlayerAttackState::doState() {
	Player* player = game->getPlayer();
	Player* bot = game->getPlayer(false);
	bool value = player->playerMove();
	OutputManager<Output>* output_manager = player->getOutputManager();
	output_manager->showField(player->getField(), bot->getField());
	if (value == true) {
		game->changeState(new PlayerWinState(game));
		//return true;   switch PlayerWinState
	}
	else {
		game->changeNextState(new BotMoveState(game));
	}
	//botmove
}

PlayerAttackState::PlayerAttackState(Game* game) : game(game) {};