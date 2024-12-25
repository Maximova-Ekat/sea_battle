#include "Scaner.h"
#include "../include/Player.h"

Scaner::Scaner(Player* player) : player(player) {};

std::string Scaner::printInfo() {
	return "Cканер";
}

bool Scaner::useAbility() {
	PlayingField* field = player->getField();
	InputManager* input_manager = player->getInputManager();
	OutputManager<Output>* output_manager = player->getOutputManager();
	std::pair<int, int> sizes = field->getSize();
	output_manager->printMessage("Введите координаты точки левого верхнего угла области 2x2 в формате [y x]\n");
	std::pair<int, int> coordinates = input_manager->inputXY(sizes.first, sizes.second);
	int x = coordinates.first - 1, y = coordinates.second - 1;
	bool is_deck = false;
	for (int i = x; i < std::min(x + 2, sizes.first); i++) {
		for (int j = y; j < std::min(y + 2, sizes.second); j++) {
			int index = field->getDeckIndex(i, j);
			if (index != -1) {
				is_deck = true;
			}
		}
	}
	if (is_deck == true) {
		output_manager->printMessage("В данной области есть сегмент корабля\n");
	}
	else {
		output_manager->printMessage("В данной области нет кораблей\n");
	}
	return false;
}
