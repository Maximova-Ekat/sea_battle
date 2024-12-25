#include "Game.h"


Game::Game(InputManager* input_manager): input_manager(input_manager) {
	output_manager = new OutputManager<Output>(out);
	player = new Player(true, input_manager, output_manager);
	bot = new Player(false, input_manager, output_manager);
	next_state = new StartState(this);
}

void Game::doState() {
	next_state->doState();
}

void Game::createGame() {
	delete next_state;
	next_state = new CreateGameState(this);
	doState();
}

void Game::quit() {
	exit(0);
}

void Game::saveGame() {
	GameState* current_state = new SaveState(this);
	current_state->doState();
	delete current_state;
}

void Game::loadGame() {
	GameState* current_state = new LoadState(this);
	current_state->doState();
	delete current_state;
}

void Game::attack() {
	delete next_state;
	next_state = new PlayerAttackState(this);
	doState();
}

void Game::useAbility() {
	delete next_state;
	next_state = new PlayerUseAbilityState(this);
	doState();
}

Player* Game::getPlayer(bool is_player) {
	if (is_player) {
		return player;
	}
	else {
		return bot;
	}
}

void Game::changeState(GameState* new_state) {
	new_state->doState();
}

json Game::to_json() const {
	json j;
	j["player"] = player->to_json();
	j["bot"] = bot->to_json();
	j["next_state"] = std::string(typeid(*next_state).name());
	return j;
}

void Game::from_json(const json& j) {
	player->from_json(j.at("player"));
	bot->from_json(j.at("bot"));
	stringToState(j.at("next_state"));
}

void Game::changeNextState(GameState* new_state) {
	delete next_state;
	next_state = new_state;
}

void Game::stringToState(std::string str) {
	if (str == "class CreateGameState") changeNextState(new CreateGameState(this));
	if (str == "class BotMoveState") changeNextState(new BotMoveState(this));
	if (str == "class BotWinState") changeNextState(new BotWinState(this));
	if (str == "class PlayerUseAbilityState") changeNextState(new PlayerUseAbilityState(this));
	if (str == "class PlayerAttackState") changeNextState(new PlayerAttackState(this));
	if (str == "class PlayerWinState") changeNextState(new PlayerWinState(this));
}

GameState* Game::getNextState() const{
	return next_state;
}

OutputManager<Output>* Game::getOutputManager() {
	return output_manager;
}

std::ofstream& operator<<(std::ofstream& out, Game* game) {
	json j = game->to_json();
	out << j.dump();
	return out;
}

std::ifstream& operator>>(std::ifstream& in, Game* game) {
	std::string json_str;
	std::getline(in, json_str);
	json j = json::parse(json_str);
	game->from_json(j);
	return in;
}

Game::~Game() {
	delete player;
	delete bot;
	delete next_state;
	delete output_manager;
}