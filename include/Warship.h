#ifndef WARSHIP_H
#define WARSHIP_H

#include <iostream>
#include <vector>
#include "json.hpp"
using json = nlohmann::json;

class Warship {
public:
	enum Damage {
		whole,
		damaged,
		destroyed
	};

private:

	std::vector <Damage> damage_ship;

	bool orientation; // True == horizontal; False == vertical

	int length;

	std::string damageToString(Damage degree) const;

	Damage stringToDamage(const std::string str);

public:

	json to_json() const;

	void from_json(const json& j);

	Warship(int length);

	Warship();

	void causeDamage(int index_deck);

	void setOrientation(bool orientation);

	bool getOrientation();

	bool isDestroyed();

	Damage getDegree(int index_deck);

	int shipLength();

	~Warship();
};
#endif