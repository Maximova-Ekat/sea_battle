#ifndef SCANER_H
#define SCANER_H

#include "Ability.h"
#include "../InputManager/include/InputManager.h"

class Scaner : public Ability {
	Player* player;
public:
	Scaner(Player* player);

	std::string printInfo() override;

	bool useAbility() override;

	~Scaner() = default;
};

#endif