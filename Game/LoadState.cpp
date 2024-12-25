#include "LoadState.h"
#include "Game.h"

void LoadState::doState() {
	std::ifstream input_file("Game.json");
	try{
		if (!input_file.good()) {
			throw OpenFileException();
		}
		input_file >> game;
	}
	catch (OpenFileException& e) {
		std::ostringstream oss;
		oss << e.what() << '\n';
		game->getPlayer()->getOutputManager()->printMessage(oss.str());
	}
	input_file.close();
	//загрузка сохранения
}

LoadState::LoadState(Game* game) : game(game) {};