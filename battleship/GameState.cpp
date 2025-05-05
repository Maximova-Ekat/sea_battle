#include "GameState.h"
#include "InteractionWithFile.h"


GameState::GameState(string filename) {
    this -> filename = filename;
}

void GameState::saving(Field* myField, ShipsManager* myShips, InteractionManager* manager) {
    this->myField = myField;
    this->myShips = myShips;
    this->manager = manager;
    enemyF = manager->getField();
    enemyS = manager->getShipsManager();
    myAbilities = manager->getAbilityManager();
    InteractionWithFile saver(filename);
    outfile = saver.open_for_save();
    saver.save(outfile, *this);
    saver.close_saving(outfile);
}



void GameState::loading(Field* myField, ShipsManager* myShips, InteractionManager* manager) {
    InteractionWithFile writer(filename);
    infile = writer.open_for_writing();
    writer.write(infile, *this);
    *myField = *this->myField;
    *myShips = *this->myShips;
    *manager = *this->manager;
    writer.close_writing(infile);
}

ostream& operator<<(ostream& os, const GameState& state) {
    json j;
    j["field_user"] = state.myField->save_to_json();
    j["enemy_field"] = state.manager->getField()->save_to_json();
    j["ship_manager_user"] = state.myShips->save_to_json();
    j["ship_manager_enemy"] = state.manager->getShipsManager()->save_to_json();
    j["abilities"] = state.manager->getAbilityManager()->save_to_json();
//    std::cout << j.dump(4);
    os << j.dump(4);
    return os;
}

istream& operator>>(istream& is, GameState& state) {
    ifstream infile(state.filename);
    string json_string((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
    json j = json::parse(json_string);
    auto size = (state.myField)->from_json_size(j["field_user"]);
    state.myShips = state.myShips->load_from_json(j["ship_manager_user"]);
    state.enemyS = state.enemyS->load_from_json(j["ship_manager_enemy"]);
    state.myField = new Field(size.first, size.second);
    state.enemyF = new Field(size.first, size.second);
    state.myField->from_json_field(j["field_user"]);
    state.enemyF->from_json_field(j["enemy_field"]);
    state.myField->addShipFromJson(state.myShips->getShips(), state.myShips->getCount());
    state.enemyF->addShipFromJson(state.enemyS->getShips(), state.enemyS->getCount());
    int s[] = {1};
    state.manager = new InteractionManager(1,1,1,s);
    state.myAbilities = new AbilityManager(state.manager);
    state.myAbilities->from_json(j["abilities"], state.manager);
    state.manager->load(state.enemyF, state.enemyS, state.myAbilities);
    return is;
}
