#ifndef BOMBING_H
#define BOMBING_H

#include "Ability.h"


class Bombing : public Ability {
	Player* player;
public:
	Bombing(Player* player);

	std::string printInfo() override;

	bool useAbility() override;

	~Bombing() = default;
};

#endif