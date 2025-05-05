#include "Field.h"
#include "../Exceptions/NoAvailableCellChangesException.h"
#include <iostream>

using json = nlohmann::json;
Field::Field(int h, int w) {
    if (h < 0 || w < 0) {
        height = 10;
        width = 10;
    }
    field = new Cell **[h];
    for (int i = 0; i < h; i++) {
        field[i] = new Cell *[w];
        for (int j = 0; j < w; j++)
            field[i][j] = new Cell;
    }
    height = h;
    width = w;
}

int Field::getHeight() const {
    return height;
}

int Field::getWidth() const {
    return width;
}
Cell *** Field::getCells() const {
    return field;
}

bool Field::isCoordinatesInField(std::pair<int, int> coords) const {
    int y = coords.first;
    int x = coords.second;
    return y >= 0 && y < height && x >= 0 && x < width;
}

bool Field::setShip(Ship& ship, std::pair<int, int> coords, Orientation orient) {
    if (not isCoordinatesInField(coords))
        throw ShipCollisionException(coords);
    if (orient == Orientation::Vertical and coords.first + ship.getLength() > height or
                                            orient == Orientation::Horizontal and coords.second + ship.getLength() > width)
        throw ShipCollisionException(coords);
    if (orient == Orientation::Vertical)
        return setShipWithAnyOrientation(ship, coords, orient, 1, 0);
    return setShipWithAnyOrientation(ship, coords, orient, 0, 1);
}

Field::Field(const Field& newField) {
    copy(newField);
}

Field::~Field() {
    deleteField();
}

Field &Field::operator = (const Field& newField) {
    deleteField();
    copy(newField);
    return *this;
}

void Field::copy(const Field& newField) {
    height = newField.height;
    width = newField.width;
    field = new Cell**[height];
    for(int i = 0; i < height; i++){
        field[i] = new Cell*[width];
        for(int j = 0; j < width; j++) {
            Cell *cell = newField.field[i][j];
            field[i][j] = new Cell(cell->getTrueState(), cell->getVisibleState());
            field[i][j]->setShip(*cell->getShip(), cell->getShipCoords());
        }
    }
}

void Field::deleteField() {
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++)
            delete field[i][j];
        delete field[i];
    }
    delete field;
}

Field::Field(Field &&newField):height(0),width(0),field(nullptr) {
    std::swap(height, newField.height);
    std::swap(width, newField.width);
    std::swap(field, newField.field);
}

Field &Field::operator = (Field &&newField) {
    if(this != &newField){
        deleteField();
        field = nullptr;
        std::swap(height, newField.height);
        std::swap(width, newField.width);
        std::swap(field, newField.field);
    }
    return *this;
}

FieldCellState Field::getCellTrueState(std::pair<int, int> coords) const {
    return field[coords.first][coords.second]->getTrueState();
}

FieldCellState Field::getCellVisibleState(std::pair<int, int> coords) const {
    return field[coords.first][coords.second]->getVisibleState();
}

bool Field::hasShip(std::pair<int, int> coords) const {
    return getCellTrueState(coords) == FieldCellState::Ship;
}

bool Field::hasDestroyedShip(std::pair<int, int> coords) const {
    return hasShip(coords) && field[coords.first][coords.second]->getShip()->isDestroyed();
}

bool Field::setShipWithAnyOrientation(Ship &ship, std::pair<int, int> coords, Orientation orient, int dx, int dy) {
    for (int i = 0; i < ship.getLength(); i++)
        if(not checkNearCellsIsEmpty({coords.first + dx * i, coords.second + dy * i}))
            throw ShipCollisionException(coords);
    for (int i = 0; i < ship.getLength(); i++) {
        field[coords.first + dx * i][coords.second + dy * i]->setTrueState(FieldCellState::Ship);
        field[coords.first + dx * i][coords.second + dy * i]->setShip(ship, i);
    }
    ship.setCoordinates(coords);
    ship.setOrientation(orient);
    return true;
}

bool Field::checkNearCellsIsEmpty(std::pair<int, int> coords) const {
    for (int j = -1; j < 2; j++)
        for (int k = -1; k < 2; k++)
            if (isCoordinatesInField({coords.first + j, coords.second + k}) and
                getCellTrueState({coords.first + j, coords.second + k}) != FieldCellState::Empty)
                return false;
    return true;
}
bool Field::cellstateIfAttack(std::pair<int, int> coords) {
    if (!isCoordinatesInField(coords))
        throw OutOfFieldAttackException(coords, {height, width});
    if(!hasShip(coords)) {
        field[coords.first][coords.second]->setVisibleState(FieldCellState::Empty);
        return false;
    }
    field[coords.first][coords.second]->setVisibleState(FieldCellState::Ship);
    return true;
}

bool Field::attack(std::pair<int, int> coords) {
    if (field[coords.first][coords.second]->getVisibleState() == FieldCellState::Empty){
        throw NoAvailableCellChangesException(coords);
    }
    if(!cellstateIfAttack(coords))
        return false;
    if (field[coords.first][coords.second]->getShip()->getSegmentState(field[coords.first][coords.second]->getShipCoords()) == ShipCellState::Destroyed){
        throw NoAvailableCellChangesException(coords);
    }
    field[coords.first][coords.second]->getShip()->changeState(field[coords.first][coords.second]->getShipCoords());
    return true;
}

bool Field::dealDoubleDamage(std::pair<int, int> coords) {
    if(!cellstateIfAttack(coords))
        return false;
    field[coords.first][coords.second]->getShip()->destroySegment(field[coords.first][coords.second]->getShipCoords());
    return true;
}

json Field::save_to_json() {
    json j;
    j["sizeFieldH"] = height;
    j["sizeFieldW"] = width;

    json field_data = json::array();
    for (int y = 0; y < height; ++y) {
        json row = json::array();
        for (int x = 0; x < width; ++x) {
            json cell;
            cell["x"] = x;
            cell["y"] = y;
            cell["status"] = static_cast<int>(field[x][y]->getVisibleState());
            cell["value"] = static_cast<int>(field[x][y]->getTrueState());
            row.push_back(cell);
        }
        field_data.push_back(row);
    }
    j["field"] = field_data;
    return j;
}

std::pair<int,int> Field::from_json_size(json j) {
    return {j["sizeFieldH"], j["sizeFieldW"]};
}

void Field::from_json_field(json j) {
    const auto& field_data = j["field"];
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const auto& cell_data = field_data[y][x];
            field[x][y]->setVisibleState(static_cast<FieldCellState>(cell_data["status"]));
            //field[x][y]->setTrueState(static_cast<FieldCellState>(cell_data["value"]));
        }
    }
}


void  Field::addShipFromJson(Ship** ships, int count){
    for(int i = 0; i < count; i++){
        setShip(*ships[i], ships[i]->getCoordinates(), ships[i]->getOrientation());
    }
}