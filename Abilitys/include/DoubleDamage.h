#ifndef DOUBLEDAMAGE_H
#define DOUBLEDAMAGE_H

#include "Ability.h"
#include "../InputManager/include/InputManager.h"

class DoubleDamage : public Ability {
	Player* player;
public:
	DoubleDamage(Player* player);

	std::string printInfo() override;

	bool useAbility() override;

	~DoubleDamage() = default;
};

#endif