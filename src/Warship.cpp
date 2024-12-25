#include "Warship.h"

std::string Warship::damageToString(Damage degree) const{
	switch (degree) {
		case whole:
			return "whole";
		case damaged:
			return "damaged";
		case destroyed:
			return "destroyed";
		default:
			return "unknown";
	}
}

Warship::Damage Warship::stringToDamage(const std::string str) {
	if (str == "whole") return whole;
	if (str == "damaged") return damaged;
	if (str == "destroyed") return destroyed;
}

json Warship::to_json() const {
	json j;
	std::vector <std::string> str_degree;
	for (const auto& degree : damage_ship) {
		str_degree.push_back(damageToString(degree));
	}
	j["length"] = length;
	j["orientation"] = orientation;
	j["damage_ship"] = str_degree;
	return j;
}

void Warship::from_json(const json& j) {
	damage_ship.clear();
	j.at("length").get_to(length);
	j.at("orientation").get_to(orientation);
	for (const auto& str : j.at("damage_ship")) {
		damage_ship.push_back(stringToDamage(str.get<std::string>()));
	}
}

Warship::Warship(int length) {
	this->length = length;
	damage_ship.resize(length);
	for (int i = 0; i < length; i++) {
		damage_ship[i] = whole;
	}
	json j = to_json();
}

Warship::Warship() = default;

void Warship::causeDamage(int index_deck) {
	switch (damage_ship[index_deck]) {
	case whole:
		damage_ship[index_deck] = damaged;
		break;
	case damaged:
		damage_ship[index_deck] = destroyed;
		break;
	}
}

void Warship::setOrientation(bool orientation) {
	this->orientation = orientation;
}

bool Warship::getOrientation() {
	return orientation;
}

bool Warship::isDestroyed() {
	for (int i = 0; i < length; i++) {
		if (damage_ship[i] != destroyed) {
			return false;
		}
	}
	return true;
}

int Warship::shipLength() {
	return length;
}

Warship::Damage Warship::getDegree(int index_deck) {
	return damage_ship[index_deck];
}

Warship::~Warship() {
	damage_ship.clear();
}