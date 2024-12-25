#include "InputManager.h"

std::pair<int, int> InputManager::inputSize() {
	int first, second;
	std::string input;
	while (true) {
		std::getline(is, input);
		std::stringstream ss(input);
		try {
			if (!(ss >> first >> second) || !ss.eof() || first <= 0 || first > 10 || second <= 0 || second > 10) {
				throw InputSizeException();
			}
			break;
		}
		catch (InputSizeException& e) {
			std::cout << e.what() << '\n';
		}

	}
	return std::make_pair(first, second);
}

int InputManager::inputValue() {
	std::string input;
	int value;
	while (true) {
		std::getline(is, input);
		std::stringstream ss(input);
		try {
			if (!(ss >> value) || !ss.eof() || (value != 1 && value != 0)) {
				throw InputValueException();
			}
			break;
		}
		catch (InputValueException& e) {
			std::cout << e.what() << '\n';
		}
	}
	return value;
}

std::pair<int, int> InputManager::inputXY(int width, int height) {
	int y, x;
	std::string input;
	while (true) {
		std::getline(is, input);
		std::stringstream ss(input);
		try {
			if (!(ss >> x >> y) || !ss.eof() || y < 1 || x < 1 || y > height || x > width) {
				throw InputCoordinatesException();
			}
			break;
		}
		catch (InputCoordinatesException& e) {
			std::cout << e.what() << '\n';
		}
	}
	return std::make_pair(x, y);
}

std::vector<int> InputManager::inputXYOrient(int width, int height) {
	int x, y, orient;
	std::string input;
	while (true) {
		std::getline(is, input);
		std::stringstream ss(input);
		try {
			if (!(ss >> x >> y >> orient) || !ss.eof() || y < 1 || x < 1 ||
				y > height || x > width || (orient != 0 && orient != 1)) {
				throw InputCoordAndOrientException();
			}
			break;
		}
		catch (InputCoordAndOrientException& e) {
			std::cout << e.what() << '\n';
		}
	}

	std::vector <int> res = { x, y, orient };
	return res;
}

Commands InputManager::stringToCommand(std::string str) {
	if (str == "c") return CREATE_GAME;
	if (str == "s") return SAVE_GAME;
	if (str == "l") return LOAD_GAME;
	if (str == "n") return NEXT_STATE;
	if (str == "q") return QUIT;
	if (str == "a") return ATTACK;
	if (str == "u") return USE_ABILITY;
	if (str == "h") return HELP;
}

Commands InputManager::inputCommand() {
	std::string input;
	json data;
	std::ifstream input_file("commands.json");
	bool is_open = true;
	if (input_file) {
		input_file >> data;
	}
	else {
		is_open = false;
	}
	input_file.close();	
	while (true) {
		std::getline(is, input);
		try {
			if (is_open) {
				if (data.contains(input)) {
					return stringToCommand(input);
				}
			}
			else {
				if (default_commands.count(input) > 0) {
					return stringToCommand(input);
				}
			}
			throw UnknownCommandException();
		}
		catch (UnknownCommandException& e) {
			std::ostringstream oss;
			oss << e.what() << '\n';
			Output out{ std::cout };
			out.printMessage(oss.str());
		}
	}
}