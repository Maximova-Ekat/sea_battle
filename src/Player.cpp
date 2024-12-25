#include "Player.h"

//Player::Player(InputManager* input_manager, OutputManager* output_manager) :
//	input_manager(input_manager), output_manager(output_manager) {};

Player::Player(bool is_player, InputManager* input_manager, OutputManager<Output>* output_manager) :
	is_player(is_player), input_manager(input_manager), output_manager(output_manager) {};

json Player::to_json() const {
	json j;
	j["ability_manager"] = ability_manager->to_json();
	j["ship_manager"] = ship_manager->to_json();
	j["field"] = field->to_json();
	j["is_player"] = is_player;
	j["is_double"] = is_double;
	return j;
}

void Player::from_json(const json& j) {
	j.at("is_double").get_to(is_double);
	j.at("is_player").get_to(is_player);

	if (field == nullptr) {
		field = new PlayingField();
	}
	if (ship_manager == nullptr) {
		ship_manager = new ShipManager();
	}
	if (ability_manager == nullptr) {
		ability_manager = new AbilityManager(this);
	}

	field->from_json(j.at("field"));
	ship_manager->from_json(j.at("ship_manager"));
	ability_manager->from_json(j.at("ability_manager"));
}

void Player::setField(int width, int height) {
	if (field != nullptr){
		delete field;
	}
	this->field = new PlayingField{ width, height };
}

void Player::setShipManager(std::vector <int> info) {
	std::pair <int, int> sizes;
	sizes = field->getSize();
	int number = info[4];
	info.pop_back();
	std::vector <int> lenghts;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < info[i]; j++) {
			lenghts.push_back(4 - i);
		}
	}
	if (ship_manager != nullptr) {
		delete ship_manager;
	}
	ship_manager = new ShipManager{ number, lenghts };
	/*if (is_player == false) {
		infoManager(number, info);
	}*/
}

void Player::setAbilityManager(bool is_new) {
	if (ability_manager == nullptr || is_new) {
		ability_manager = new AbilityManager(this);
	}
	/*if (this->ability_manager != nullptr) {
		delete this->ability_manager;
	}
	if (ability_manager != nullptr) {
		this->ability_manager = ability_manager;
	}
	else {
		this->ability_manager = new AbilityManager();
	}*/
}

PlayingField* Player::getField() {
	return this->field;
}

ShipManager* Player::getShipManager() {
	return this->ship_manager;
}

AbilityManager* Player::getAbilityManager() {
	return this->ability_manager;
}

InputManager* Player::getInputManager() {
	return this->input_manager;
}

OutputManager<Output>* Player::getOutputManager() {
	return this->output_manager;
}

void Player::setDouble() {
	this->is_double = true;
}

bool Player::playerMove(bool is_use) {
	output_manager->printMessage("------------------------\n");
	if (is_player == true) {
		output_manager->printMessage("Ваш ход!\n");
	}
	else {
		output_manager->printMessage("Ход противника!\n");
	}
	if (is_use) {
		try {
			int number_abilitys = ability_manager->getNumber();
			if (number_abilitys == 0) {
				throw UseAbilityException();
			}
			else {
				std::ostringstream oss;
				oss << "Активируется способность " << ability_manager->infoAbility() << '\n';
				output_manager->printMessage(oss.str());
				ability_manager->useAbility();
				bool check_win = ship_manager->checkWin();
				if (check_win == true) {
					return true;
				}
				return false;
			}
		}
		catch (UseAbilityException& e) {
			std::ostringstream oss;
			oss << e.what() << '\n';
			output_manager->printMessage(oss.str());
		}
	}
	else {
		std::pair <int, int> sizes;
		int y, x;
		sizes = field->getSize();
		if (is_player == true) {
			output_manager->printMessage(" - Укажите точку удара в формате [x y]\n");
			std::pair <int, int> coordinates = input_manager->inputXY(sizes.first, sizes.second);
			x = --coordinates.first;
			y = --coordinates.second;
		}
		else {
			std::pair <int, int> coordinates;
			RandomValues* random_values = new RandomValues();
			coordinates = random_values->getRandomCoordinates(sizes);
			delete random_values;
			y = --coordinates.second;
			x = --coordinates.first;
		}
		int check;
		check = field->cellAtack(x, y);
		if (check != 0) {
			bool check_hit;
			if (is_double == true) {
				field->cellAtack(x, y);
				check_hit = hit(x, y, check - 1, true);
			}
			check_hit = hit(x, y, check - 1);
			if (check_hit == false) {
				return playerMove(false);
			}
			bool check_win = ship_manager->checkWin();
			if (check_win == true) {
				return true;
			}
		}
		else {
			output_manager->printMessage("Промах!\n");
		}
		is_double = false;
	}
	return false;
}

bool Player::hit(int x, int y, int index, bool is_hide) {
	int index_deck = field->getDeckIndex(x, y);
	bool degree = ship_manager->checkDegree(index, index_deck);
	if (degree == true) {
		if (is_hide == false) { output_manager->printMessage("Попадание в уничтоженный сегмент корабля!\n"); }
		return false;
	}
	else {
		ship_manager->setDamage(index, index_deck);

		bool check = ship_manager->checkDestroyed(index);
		bool degree = ship_manager->checkDegree(index, index_deck);

		if (is_hide == false) { output_manager->printMessage("Попадание!\n"); }
		if (degree == false) {
			if (is_hide == false) { output_manager->printMessage("Сектор поврежден!\n"); }
		}
		else {
			if (is_hide == false) { output_manager->printMessage("Сектор уничтожен!\n"); };
			field->killDeck(x, y);
		}

		if (check == true) {
			if (is_player == true) { ability_manager->createAbility(); }
			if (is_hide == false) { output_manager->printMessage("Корабль уничтожен!\n"); }
		}
	}
	return true;
}

Player::~Player() {
	delete field;
	delete ship_manager;
	if (is_player == true) { delete ability_manager; }
}