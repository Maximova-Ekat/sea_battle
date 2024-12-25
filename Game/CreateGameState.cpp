#include "CreateGameState.h"
#include "Game.h"

void CreateGameState::doState() {
	Player* player = game->getPlayer();
	Player* bot = game->getPlayer(false);
	CreatePlayer first = CreatePlayer(bot, true);
	std::pair<int, int> sizes = bot->getField()->getSize();
	CreatePlayer second = CreatePlayer(player, false, sizes.first, sizes.second, true);

	game->changeNextState(new PlayerUseAbilityState(game));
}

CreateGameState::CreateGameState(Game* game) : game(game) {};