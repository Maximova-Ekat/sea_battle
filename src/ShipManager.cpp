#include "ShipManager.h"

void ShipManager::createShip() {
	for (int i = 0; i < number; i++) {
		Warship* ship = new Warship(lengths[i]);
		ships.push_back(ship);
	}
}

ShipManager::ShipManager(int number, std::vector <int> lengths) {
	this->number = number;
	this->lengths = lengths;
	createShip();
}

ShipManager::ShipManager() = default;

json ShipManager::to_json() const {
	json j;
	j["number"] = number;
	j["lengths"] = lengths;
	json j_ships = json::array();
	for (const auto& ship : ships) {
		j_ships.push_back(ship->to_json());
	}
	j["ships"] = j_ships;
	return j;
}

void ShipManager::from_json(const json& j) {
	j.at("number").get_to(number);
	j.at("lengths").get_to(lengths);
	ships.clear();
	int i = 0;
	for (const auto& ship : j.at("ships")) {
		ships.push_back(new Warship);
		ships[i++]->from_json(ship);
	}
}

std::vector <int> ShipManager::getLengths() {
	return lengths;
}

int ShipManager::getShipLength(int index) {
	return this->lengths[index];
}

Warship* ShipManager::getWarship(int index) {
	return ships[index];
}

void ShipManager::setOrientation(int index, bool orientation) {
	ships[index]->setOrientation(orientation);
}

void ShipManager::setDamage(int index_ship, int index_deck) {
	ships[index_ship]->causeDamage(index_deck);
}

bool ShipManager::getOrientation(int index) {
	return ships[index]->getOrientation();
}

bool ShipManager::checkDegree(int index, int index_deck) {
	Warship::Damage degree;
	degree = ships[index]->getDegree(index_deck);
	switch (degree) {
	case Warship::whole:
	case Warship::damaged:
		return false;
	case Warship::destroyed:
		return true;
	}
}

bool ShipManager::checkDestroyed(int index) {
	return ships[index]->isDestroyed();
}

bool ShipManager::checkWin() {
	for (int i = 0; i < ships.size(); i++) {
		if (ships[i]->isDestroyed() == false) {
			return false;
		}
	}
	return true;
}

int ShipManager::getNumber() {
	return this->number;
}

ShipManager::~ShipManager() {
	for (Warship* ptr : ships) {
		delete ptr;
	}
	ships.clear();
	lengths.clear();
}