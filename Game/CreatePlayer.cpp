#include "CreatePlayer.h"

CreatePlayer::CreatePlayer(Player* player, bool is_player, int width, int height, bool is_new): 
	player(player), is_player(is_player), width(width), height(height), is_new(is_new) {
	input_manager = player->getInputManager();
	output_manager = player->getOutputManager();
	if (is_player) {
		inputSizes();
	}
	else {
		createPlayer();
		randomCoordinates();
	}
}

void CreatePlayer::createPlayer(bool is_hide) {
	player->setField(width, height);
	setManager(is_hide);
}

void CreatePlayer::setManager(bool is_hide) {
	std::vector <int> info;
	info = countShip(width, height);
	player->setShipManager(info);
	player->setAbilityManager(is_new);
	int number = info[4];
	info.pop_back();
	if (!is_hide && is_player) {
		infoManager(number, info);
	}
}

void CreatePlayer::infoManager(int number, std::vector <int> lenghts) {
	OutputManager<Output>* output_manager = player->getOutputManager();
	std::ostringstream oss;
	oss << "¬ игре будет " << number << " кораблей.\n";
	output_manager->printMessage(oss.str());
	for (int i = 0; i < 4; i++) {
		oss.str("");
		oss.clear();
		oss << lenghts[i] << " " << 4 - i << "-палубных кораблей;\n";
		output_manager->printMessage(oss.str());
	}
}

std::vector <int> CreatePlayer::countShip(int width, int height) {
	int area = height * width;
	int count = ceil(area * 0.2);
	std::vector <int> arr;
	int number;
	int first = 0, second = 0, third = 0, fourth = 0;
	if (area <= 100) {
		for (int f = 1; f < 5; f++) {
			for (int s = 0; s < ceil(count * 0.5 / 2); s++) {
				for (int t = 0; t < ceil(count * 0.45 / 3); t++) {
					for (int fr = 0; fr < ceil(count * 0.26 / 4); fr++) {
						if (f + s * 2 + t * 3 + fr * 4 == count) {
							if (fr <= t && t <= s && s <= f) {
								arr.clear();
								arr.push_back(fr);
								arr.push_back(t);
								arr.push_back(s);
								arr.push_back(f);
								number = fr + t + s + f;
							}
						}
					}
				}
			}
		}
	}
	else {
		for (int f = 1; f < ceil(count * 0.25); f++) {
			for (int s = 0; s < ceil(count * 0.4 / 2); s++) {
				for (int t = 0; t < ceil(count * 0.4 / 3); t++) {
					for (int fr = 0; fr < ceil(count * 0.31 / 4); fr++) {
						if (f + s * 2 + t * 3 + fr * 4 == count) {
							if (fr <= t && t <= s && s <= f) {
								arr.clear();
								arr.push_back(fr);
								arr.push_back(t);
								arr.push_back(s);
								arr.push_back(f);
								number = fr + t + s + f;
							}
						}
					}
				}
			}
		}
	}
	arr.push_back(number);
	return arr;
}

void CreatePlayer::inputSizes() {
	std::cout << " - ¬ведите размер пол€ в формате: [ширина высота]\n";
	srand(time(0));
	std::pair<int, int> sizes = input_manager->inputSize();
	width = sizes.first;
	height = sizes.second;
	createPlayer();
	inputAnswer();
}

void CreatePlayer::inputAnswer(bool new_iteration) {
	output_manager->printMessage(" - ≈сли хотите расставить корабли вручную, введите [1]\n - ≈сли хотите, чтобы корабли были расставлены автоматически, введите [0]\n");
	int value = input_manager->inputValue();

	if (value == 1) {
		inputCoordinates();
	}
	else {
		randomCoordinates();
	}
}

void CreatePlayer::inputCoordinates() {
	ShipManager* player_manager = player->getShipManager();
	PlayingField* player_field = player->getField();
	std::vector <int> lenghts = player_manager->getLengths();
	int i = 0;
	std::pair <int, int> sizes = player_field->getSize();
	while (i < lenghts.size()) {
		std::ostringstream oss;
		oss << " - ¬ведите координаты корабл€ размера " << lenghts[i] << " и его ориентацию на поле в формате: [y x orientation]\n";
		output_manager->printMessage(oss.str());
		output_manager->printMessage(" - y и x - координаты левого верхнего угла коробл€, orientation - его ориентаци€ на поле, при этом 1 - горизонтально, 0 - вертикально.\n");
		int x, y, orient;
		std::vector <int> input_values = input_manager->inputXYOrient(sizes.first, sizes.second);
		x = input_values[0];
		y = input_values[1];
		orient = input_values[2];
		bool orientation;
		if (orient == 1) {
			orientation = true;
		}
		else {
			orientation = false;
		}
		Warship* ship = player_manager->getWarship(i);

		bool check;
		try {
			check = player_field->setShip(ship, x, y, orientation, i + 1);
			if (check == false) {
				throw SetShipException();
			}
			player_manager->setOrientation(i, orientation);
			i++;
			output_manager->printFieldIndex(sizes, player_field->getViewIndex());
		}
		catch (SetShipException& e) {
			std::ostringstream oss;
			oss << e.what() << '\n';
			output_manager->printMessage(oss.str());
		}
	}
}

void CreatePlayer::randomCoordinates() {
	PlayingField* field = player->getField();
	ShipManager* ship_manager = player->getShipManager();
	std::vector <int> lenghts = ship_manager->getLengths();
	int i = 0;
	auto begin = std::chrono::steady_clock::now();
	std::pair<int, int> sizes = field->getSize();
	while (i < lenghts.size()) {
		try {
			auto end = std::chrono::steady_clock::now();
			auto elapsed_ms = std::chrono::duration<double>(end - begin);
			if (elapsed_ms.count() > 2) {
				throw RandomSetShipException();
			}
		}
		catch (RandomSetShipException& e) {
			createPlayer(true);
			i = 0;
			begin = std::chrono::steady_clock::now();
			output_manager->printMessage("–асстановка кораблей..\n");
		}
		int orient;
		orient = rand() % 2;
		RandomValues* random_values = new RandomValues;
		std::pair <int, int> coordinates = random_values->getRandomCoordinates(sizes);
		delete random_values;
		bool orientation;

		if (orient == 1) {
			orientation = true;
		}
		else {
			orientation = false;
		}

		bool check;
		check = pseudoRandom(coordinates.first, coordinates.second, orientation, i, is_player);
		if (check == true) {
			ship_manager->setOrientation(i, orientation);
			i++;
		}
	}
}

bool CreatePlayer::pseudoRandom(int x, int y, bool orientation, int number, bool is_player) {
	PlayingField* field = player->getField();
	ShipManager* ship_manager = player->getShipManager();
	std::pair <int, int> sizes = field->getSize();
	for (int i = x; i <= sizes.first; i++) {
		for (int j = y; j <= sizes.second; j++) {
			Warship* ship = ship_manager->getWarship(number);
			bool check = field->setShip(ship, i, j, orientation, number + 1);
			if (check == true) {
				return true;
			}
		}
	}
	return false;
}