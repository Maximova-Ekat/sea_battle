#include <iostream>
#include <vector>
#include "ShipsManager.h"

using json = nlohmann::json;
ShipsManager::ShipsManager(int count, int* size) {
    sizes = size;
    ships = new Ship * [count];
    for(int i = 0; i < count; i++)
        ships[i] = new Ship(sizes[i]);
    this->count = count;
}

ShipsManager::~ShipsManager() {
    for(int i = 0; i < count; i++)
        delete ships[i];
    delete ships;
}
int* ShipsManager::getSizes() {
    return sizes;
}

Ship **ShipsManager::getShips() {
    return ships;
}

Ship& ShipsManager::getShip(int index) const {
    if (index < 0 || index >= count)
        throw std::invalid_argument("Invalid ship index");
    return *ships[index];

}

int ShipsManager::getCount() {
    return count;
}

bool ShipsManager::allDestroyed() {
    int destroyedCount=0;
    for (int i = 0; i < count; i++) {
        if (ships[i]->isDestroyed())
            destroyedCount++;
    }
    return destroyedCount == count;
}

void ShipsManager::print() {
    for(int i = 0; i < count; i++){
        std::cout << "ship " << i+1 << std::endl;
        ships[i]->print();
    }
}

json ShipsManager::save_to_json() {
    json j;
    for (int k = 0; k < count; k++) {
        Ship* ship = ships[k];
        json ship_data;
        ship_data["size"] = ship->getLength();
        ship_data["orientation"] = static_cast<int>(ship->getOrientation());
        ship_data["coordinates"] = ship->getCoordinates();
        json segments_data = json::array();
        for (int i = 0; i < ship->getLength(); i++) {
            json segment_data;
            segment_data["id"] = i;
            segment_data["status"] = static_cast<ShipCellState>(ship->getSegmentState(i));
            segments_data.push_back(segment_data);
        }
        ship_data["segments"] = segments_data;
        j["ships"].push_back(ship_data);
    }
    return j;
}

ShipsManager* ShipsManager::load_from_json(json j) {
    std::vector<int> sizes = getSizesFromJson(j);
    ShipsManager* manager = new ShipsManager(static_cast<int>(sizes.size()), sizes.data());
    int k = 0;
    for (auto& ship_data : j["ships"]) {
        int size = ship_data["size"];

        Ship* ship = new Ship(size);
        ship->setOrientation(static_cast<Orientation>(ship_data["orientation"]));
        ship->setCoordinates(ship_data["coordinates"]);

        for (auto& segment_data : ship_data["segments"]) {
            ship->setSegmentState(segment_data["id"], static_cast<ShipCellState>(segment_data["status"]));
        }

        manager->ships[k] = ship;
        k++;
    }

    return manager;
}

std::vector<int> ShipsManager::getSizesFromJson(json j) {
    std::vector<int> shipSizes;

    for (const auto& ship : j["ships"]) {
        shipSizes.push_back(ship["size"]);
    }

    return shipSizes;
}

void ShipsManager::genNewShips() {
    for(int i = 0; i < count; i++)
        delete ships[i];
    ships = new Ship * [count];
    for(int i = 0; i < count; i++)
        ships[i] = new Ship(sizes[i]);
}
