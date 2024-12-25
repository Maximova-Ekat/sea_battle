#include "DoubleDamage.h"
#include "../include/Player.h"

DoubleDamage::DoubleDamage(Player* player) : player(player) {};

std::string DoubleDamage::printInfo() {
	return "Двойной урон";
}

bool DoubleDamage::useAbility() {
	/*std::pair<int, int> sizes = field->getsize();
	std::cout << "введите координаты точки атаки в формате [y x]\n";
	input* input = new input();
	std::pair<int, int> coordinates = input->inputyx(sizes.first, sizes.second);
	int y = coordinates.first - 1, x = coordinates.second - 1;
	delete input;
	int index;
	for (int i = 0; i < 2; i++) {
		index = field->cellatack(y, x) - 1;
		if (index != -1) {
			bool check = manager->checkdestroyed(index);
			if (check == false) {
				int index_deck = field->getdeckindex(y, x);
				manager->setdamage(index, index_deck);
			}
		}
	}
	if (index == -1) {
		std::cout << "промах!\n";
	}
	else {
		std::cout << "попадание!\nсектор уничтожен!\n";
		field->killdeck(y, x);
		bool check = manager->checkdestroyed(index);
		if (check == true) {
			std::cout << "корабль уничтожен!\n";
			return true;
		}
	}
	return false;*/
	player->setDouble();
	return false;
}