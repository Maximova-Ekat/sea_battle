#include "AbilityManager.h"

std::string AbilityManager::abilityToString(Ability* ability) const{
	std::string name_ability = ability->printInfo();
	if (name_ability == "Бомбардировка") return "Bombing";
	if (name_ability == "Двойной урон") return "DoubleDamage";
	if (name_ability == "Cканер") return "Scaner";
}

json AbilityManager:: to_json() const {
	json j;
	j["number"] = number;
	json j_array = json::array();
	for (const auto& ability: ability_queue) {
		j_array.push_back(abilityToString(ability));
	}
	j["ability_queue"] = j_array;
	return j;
}

void AbilityManager::from_json(const json& j) {
	j.at("number").get_to(number);
	ability_queue.clear();
	for (const auto& abilitys : j.at("ability_queue")) {
		if (abilitys == "Bombing") ability_queue.push_back(new Bombing (player));
		if (abilitys == "DoubleDamage") ability_queue.push_back(new DoubleDamage(player));
		if (abilitys == "Scaner") ability_queue.push_back(new Scaner(player));
	}
}

AbilityManager::AbilityManager(Player* player): player(player) {
	ability_queue.push_back(new Bombing(player));
	ability_queue.push_back(new DoubleDamage(player));
	ability_queue.push_back(new Scaner(player));

	std::mt19937 g(static_cast<unsigned int>(time(0)));
	std::shuffle(ability_queue.begin(), ability_queue.end(), g);

	this->number = 3;
}

AbilityManager::AbilityManager(const AbilityManager& other) :number(other.number), ability_queue(other.ability_queue) {} //копирование

AbilityManager::AbilityManager(AbilityManager&& other) noexcept : number(other.number), ability_queue(std::move(other.ability_queue)) { //перемещение	
	other.number = 0;
}

AbilityManager& AbilityManager::operator=(const AbilityManager& other) {
	if (this != &other) {
		number = other.number;
		ability_queue = other.ability_queue;
	}
	return *this;
}

AbilityManager& AbilityManager::operator=(AbilityManager&& other) noexcept {
	if (this != &other) {
		number = other.number;
		ability_queue = std::move(other.ability_queue);
		other.number = 0;
	}
	return *this;
}

void AbilityManager::createAbility() {
	std::vector<Ability*> new_abilitys = { new DoubleDamage(player), new Scaner(player), new Bombing(player)};

	std::mt19937 g(static_cast<unsigned int>(time(0)));
	std::shuffle(new_abilitys.begin(), new_abilitys.end(), g);

	this->ability_queue.resize(number + 1);
	this->ability_queue[number] = new_abilitys[0];
	this->number++;

}

std::string AbilityManager::infoAbility() {
	return ability_queue[0]->printInfo();
}

void AbilityManager::useAbility() {
	bool check = ability_queue[0]->useAbility();
	ability_queue.erase(ability_queue.begin());
	this->number--;
	if (check == true) {
		createAbility();
	}
}

int AbilityManager::getNumber() const {
	return this->number;
}

AbilityManager::~AbilityManager() {
	ability_queue.clear();
}