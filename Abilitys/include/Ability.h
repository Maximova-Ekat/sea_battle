#ifndef ABILITY_H
#define ABILITY_H

#include <iostream>
#include "../include/ShipManager.h"
#include "../include/PlayingField.h"

class Player;
class Ability {
public:
	virtual std::string printInfo() = 0;

	virtual bool useAbility() = 0;
};

#endif