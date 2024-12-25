#include <iostream>
#include <windows.h>
#include "GameController.h"

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	InputManager* input_manager = new InputManager(std::cin);
	Game game = Game{ input_manager };
	GameController<InputManager> game_controller = GameController{ input_manager, game };
}