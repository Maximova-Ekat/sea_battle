#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H

#include <iostream>
#include <vector>
#include "Warship.h"

class ShipManager {
private:
	std::vector <int> lengths;
	std::vector <Warship*> ships;
	int number;

	void createShip();


public:
	ShipManager(int number, std::vector <int> lenghts);
	ShipManager();

	json to_json() const;

	void from_json(const json& j);

	std::vector <int> getLengths();

	int getShipLength(int index);

	Warship* getWarship(int index);

	void setOrientation(int index, bool orientation);

	void setDamage(int index_ship, int index_deck);

	bool getOrientation(int index);

	bool checkDegree(int index, int index_deck);

	bool checkDestroyed(int index);

	bool checkWin();

	int getNumber();

	~ShipManager();
};

#endif