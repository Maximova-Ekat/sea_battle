#include "Ship/Ship.h"
#include "json.hpp"

#ifndef BATTLESHIP_SHIPSMANAGER_H
#define BATTLESHIP_SHIPSMANAGER_H

using json = nlohmann::json;
class ShipsManager {
private:
    int count;
    int* sizes;
    Ship** ships;

public:
    ShipsManager(int count, int* size);
    Ship** getShips();
    Ship& getShip(int index) const;
    int getCount();
    bool allDestroyed();
    void print();
    std::vector<int> getSizesFromJson(json j);
    json save_to_json();
    ShipsManager* load_from_json(json j);
    ~ShipsManager();

    int *getSizes();
    void genNewShips();
};

#endif //BATTLESHIP_SHIPSMANAGER_H
