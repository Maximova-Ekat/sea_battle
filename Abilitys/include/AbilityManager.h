#ifndef ABILITYMANAGER_H
#define ABILITYMANAGER_H

#include <algorithm>
#include <random>
#include <vector>
#include <string>
#include <sstream>
#include "DoubleDamage.h"
#include "Bombing.h"
#include "Scaner.h"
#include "../Exception/include/Exception.h"


class AbilityManager {
private:
	int number;
	std::vector<Ability*> ability_queue;
	Player* player;

public:

	std::string abilityToString(Ability* ability) const;

	json to_json() const;

	void from_json(const json& j);

	AbilityManager(Player* player);

	AbilityManager(const AbilityManager& other);

	AbilityManager(AbilityManager&& other) noexcept;

	AbilityManager& operator=(const AbilityManager& other);

	AbilityManager& operator=(AbilityManager&& other) noexcept;

	void createAbility();

	std::string infoAbility();

	void useAbility();

	int getNumber() const;

	~AbilityManager();
};

#endif