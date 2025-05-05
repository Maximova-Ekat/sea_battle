#include "Cell.h"
#include "../Exceptions/OutOfFieldAttackException.h"
#include "../Exceptions/ShipCollisionException.h"
#include "../json.hpp"
#include<vector>
#ifndef BATTLESHIP_FIELD_H
#define BATTLESHIP_FIELD_H

using json = nlohmann::json;
class Field {
private:
    int height;
    int width;
    Cell*** field;
    bool setShipWithAnyOrientation(Ship& ship, std::pair<int, int> coords, Orientation orient, int dx, int dy);
    bool checkNearCellsIsEmpty(std::pair<int, int> coords) const;
    bool checkAndSetState(std::pair<int, int> coords);
public:
    Field(int h, int w);
    Field(const Field& newField);
    Field& operator = (const Field& newField);
    Field(Field&& newField);
    Field& operator = (Field&& newField);
    int getHeight() const;
    int getWidth() const;
    Cell*** getCells() const;
    bool setShip(Ship& ship, std::pair<int, int> coords, Orientation orient);
    bool isCoordinatesInField(std::pair<int, int> coords) const;
    FieldCellState getCellTrueState(std::pair<int, int> coords) const;
    bool attack(std::pair<int, int> coords);
    bool dealDoubleDamage(std::pair<int, int> coords);
    void deleteField();
    void copy(const Field& newField);
    json save_to_json();
    std::pair<int,int> from_json_size(json j);
    void from_json_field(json j);
    void addShipFromJson(Ship** ships, int count);
    ~Field();

    FieldCellState getCellVisibleState(std::pair<int, int> coords) const;

    bool hasShip(std::pair<int, int> coords) const;

    bool hasDestroyedShip(std::pair<int, int> coords) const;

    bool cellstateIfAttack(std::pair<int, int> coords);
};

#endif //BATTLESHIP_FIELD_H
