#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Game.h"
#include "InputManager.h"

template <typename InputClass>
class GameController {
	Game& game;
	InputClass* input;

public:
	GameController(InputClass* input, Game& game) : input(input), game(game) { inputCommand(); };

	void inputCommand() {
		game.getOutputManager()->printMessage("¬ведите команду\n");
		Commands current_command = input->inputCommand();
		checkCommand(current_command);
		inputCommand();
	}

	void checkCommand(Commands current_command) {
		GameState* next_state = game.getNextState();
		OutputManager<Output>* output_manager = game.getOutputManager();
		switch (current_command) {
		case CREATE_GAME:
			game.createGame();
			break;
		case SAVE_GAME:
			try {
				if (!dynamic_cast<StartState*>(next_state)) {
					game.saveGame();
				}
				else {
					throw SaveCommandException();
				}
			}
			catch (SaveCommandException& e) {
				std::ostringstream oss;
				oss << e.what() << '\n';
				output_manager->printMessage(oss.str());
			}
			break;
		case LOAD_GAME:
			game.loadGame();
			break;
		case NEXT_STATE:
			game.doState();
			break;
		case QUIT:
			game.quit();
			break;
		case ATTACK:
			try {
				if (dynamic_cast<PlayerAttackState*>(next_state) || dynamic_cast<PlayerUseAbilityState*>(next_state)) {
					game.attack();
				}
				else {
					throw AttackCommandException();
				}
			}
			catch (AttackCommandException& e) {
				std::ostringstream oss;
				oss << e.what() << '\n';
				output_manager->printMessage(oss.str());
			}
			break;
		case USE_ABILITY:
			try {
				if (dynamic_cast<PlayerUseAbilityState*>(next_state)) {
					game.useAbility();
				}
				else {
					throw UseAbilityCommandException();
				}
			}
			catch (UseAbilityCommandException& e) {
				std::ostringstream oss;
				oss << e.what() << '\n';
				output_manager->printMessage(oss.str());
			}
			break;
		case HELP:
			output_manager->help();
			break;
		}
	}
};

#endif
