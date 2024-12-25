#include "PlayingField.h"

void PlayingField::createField() {
	field_view.resize(height, std::vector <Condition>(width, Condition::unknown));
	field_value.resize(height, std::vector <std::pair<int,int>>(width, std::make_pair(0,-1)));
}

bool PlayingField::checkNeighbors(int length, int x, int y, bool orientation) {
	if (orientation == true) {
		for (int i = std::max(0, y - 1); i < std::min(y + 2, height); i++) {
			for (int j = std::max(0, x - 1); j - x <= int(length) && j < width; j++) {
				if (field_value[i][j].first != 0) {
					return false;
				}
			}
		}
	}
	else {
		for (int i = std::max(0, y - 1); i - y <= int(length) && i < height; i++) {
			for (int j = std::max(0, x - 1); j < std::min(x + 2, width); j++) {
				if (field_value[i][j].first != 0) {
					return false;
				}
			}
		}
	}
	return true;
}

bool PlayingField::checkCorrect(int length, int x, int y, bool orientation) {
	if (x < 0 || y < 0 || x > width || y > height) {
		return false;
	}
	int count = 0;
	if (orientation == true) {
		for (int j = x; j < x + length && j < width; j++) {
			count++;
		}
	}
	else {
		for (int i = y; i < y + length && i < height; i++) {
			count++;
		}
	}
	if (count != length) {
		return false;
	}
	return true;
}

PlayingField::PlayingField(int width, int height) {
	this->height = height;
	this->width = width;
	createField();
}

PlayingField::PlayingField() = default;

PlayingField::PlayingField(const PlayingField& other) : //копирование
	field_value(other.field_value), field_view(other.field_view),
	height(other.height), width(other.width) {}

PlayingField::PlayingField(PlayingField&& other) noexcept : //перемещение	
	field_value(std::move(other.field_value)), field_view(std::move(other.field_view)),
	height(other.height), width(other.width) {
	other.height = 0;
	other.width = 0;
}

PlayingField& PlayingField::operator=(const PlayingField& other) {
	if (this != &other) {
		field_view = other.field_view;
		field_value = other.field_value;
		height = other.height;
		width = other.width;
	}
	return *this;
}

PlayingField& PlayingField::operator=(PlayingField&& other) noexcept {
	if (this != &other) {
		field_value = std::move(other.field_value);
		field_view = std::move(other.field_view);
		height = other.height;
		width = other.width;

		other.height = 0;
		other.width = 0;
	}
	return *this;
}

std::string PlayingField::conditionToString(Condition condition) const {
	switch (condition) {
	case unknown:
		return "unknown";
	case hide:
		return "hide";
	case damaged:
		return "damaged";
	case destroyed:
		return "destroyed";
	case empty:
		return "empty";
	}
}

PlayingField::Condition PlayingField::stringToCondition(const std::string str) {
	if (str == "unknown") return unknown;
	if (str == "hide") return hide;
	if (str == "damaged") return damaged;
	if (str == "destroyed") return destroyed;
	if (str == "empty") return empty;
}

json PlayingField::to_json() const {
	json j;
	j["height"] = height;
	j["width"] = width;

	json j_array_view = json::array();
	json j_array_value = json::array();

	for (int i = 0; i < height; i++) {
		json j_array_view_add = json::array();
		json j_array_value_add = json::array();

		for (int j = 0; j < width; j++) {
			j_array_view_add.push_back(conditionToString(field_view[i][j]));

			json j_pair;
			j_pair["first"] = field_value[i][j].first;
			j_pair["second"] = field_value[i][j].second;
			j_array_value_add.push_back(j_pair);
		}

		j_array_view[i] = j_array_view_add;
		j_array_value[i] = j_array_value_add;
	}
	j["field_view"] = j_array_view;
	j["field_value"] = j_array_value;
	return j;
}

void PlayingField::from_json(const json& j) {
	j.at("height").get_to(height);
	j.at("width").get_to(width);

	if (field_value.size() > 0) {
		createField();
		for (int i = 0; i < height; i++) {
			field_value[i].clear();
			field_view.clear();
		}
		field_value.clear();
		field_view.clear();
	}

	for (const auto& row : j.at("field_view")) {
		std::vector<Condition> row_condition;
		for (const auto& condition : row) {
			row_condition.push_back(stringToCondition(condition));
		}
		field_view.push_back(row_condition);
	}

	for (const auto& row : j.at("field_value")) {
		std::vector<std::pair<int, int>> row_pair;
		for (const auto& j_pair : row) {
			int first = j_pair["first"].get<int>();
			int second = j_pair["second"].get<int>();
			row_pair.push_back(std::make_pair(first, second));
		}
		field_value.push_back(row_pair);
	}
}

std::pair <int, int> PlayingField::getSize() {
	std::pair <int, int> sizes(width, height);
	return sizes;
}

bool PlayingField::setShip(Warship* ship, int x, int y, bool orientation, int value) {
	x--;
	y--;
	int length = ship->shipLength();																	
	if (checkCorrect(length, x, y, orientation) == false) {																				//error
		return false;
	}
	if (checkNeighbors(length, x, y, orientation) == false) {																				//error
		return false;
	}

	if (orientation == true) {
		for (int j = x; j < x + length; j++) {
			field_value[y][j].first = value;
			field_value[y][j].second = j - x;
		}
	}
	else {
		for (int i = y; i < y + length; i++) {
			field_value[i][x].first = value;
			field_value[i][x].second = i - y;
		}
	}
	return true;
}

int PlayingField::cellAtack(int x, int y, bool is_hide) {
	if (field_value[y][x].first == 0) {
		field_view[y][x] = empty;
		return 0;
	}
	else {
		switch(field_view[y][x]) {
		case unknown:
			if (is_hide == true) {
				field_view[y][x] = hide;
			}
			else {
				field_view[y][x] = damaged;
			}
			break;
		case damaged:
		case hide:
			field_view[y][x] = destroyed;
			break;
		default:
			break;
		}
		return field_value[y][x].first;
	}
}

void PlayingField::killDeck(int x, int y) {
	field_value[y][x].second = -1;
}

int PlayingField::getDeckIndex(int x, int y) {
	return field_value[y][x].second;
}

std::vector<std::vector<PlayingField::Condition>> PlayingField::getView() {
	return this->field_view;
}

std::vector<std::vector<std::pair<int, int>>> PlayingField::getViewIndex() {
	return this->field_value;
}

PlayingField::~PlayingField() {
	for (int i = 0; i < height; i++) {
		field_value[i].clear();
		field_view[i].clear();
	}
	field_value.clear();
	field_view.clear();
}