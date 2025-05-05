#include "Ship.h"
#include <iostream>

Ship::Ship(int len) {
    if(len < 1)
        this->len = 1;
    else if(len > 4)
        this->len = 4;
    else
        this->len = len;
    for(int i = 0; i < this->len; i++)
        state[i] = ShipCellState::Whole;
}

int Ship::getLength() const {
    return len;
}

std::pair<int, int> Ship::getCoordinates() {
    return coordinates;
}

Orientation Ship::getOrientation() {
    return orientation;
}

ShipCellState Ship::getSegmentState(int numberOfCell) {
    if (numberOfCell < 0 || numberOfCell >= len) {
        throw std::out_of_range("Segment index out of range.");
    }
    return state[numberOfCell];
}

ShipCellState Ship::getSegmentState(std::pair<int, int> point) {
    int x = point.first - coordinates.first;
    int y = point.second - coordinates.second;
    if (x < 0 || x >= len || y < 0 || y >= len) {
        throw std::out_of_range("Segment index out of range.");
    }
    int p = x;
    if(y > x) p = y;
    return state[p];
}

std::pair<int, int> Ship::getSegmentCoordinates(int segmentIndex) {
    if (orientation == Orientation::Horizontal)
        return {coordinates.first + segmentIndex, coordinates.second};
    return {coordinates.first, coordinates.second + segmentIndex};
}

void Ship::setCoordinates(std::pair<int, int> coords) {
    coordinates = coords;
}

void Ship::setOrientation(Orientation orient) {
    orientation = orient;
}

void Ship::changeState(int numberOfCell) {
    if(state[numberOfCell] == ShipCellState::Whole)
        state[numberOfCell] = ShipCellState::Damaged;
    else if(state[numberOfCell] == ShipCellState::Damaged)
        state[numberOfCell] = ShipCellState::Destroyed;
}

void Ship::destroySegment(int numberOfCell) {
    state[numberOfCell] = ShipCellState::Destroyed;
}

bool Ship::isDestroyed() {
    for(int i = 0; i < len; i++)
        if(state[i] != ShipCellState::Destroyed)
            return false;
    return true;
}

using namespace std;
void Ship::print() {
    cout << "len: " << len << endl;
    cout << "coords: (" << coordinates.first << ';' << coordinates.second << ")\n";
    for(int i = 0; i < len; i++){
        if(state[i] == ShipCellState::Whole)
            cout << "+";
        else if(state[i] == ShipCellState::Damaged)
            cout << "=";
        else
            cout << "-";
    }
    cout << endl;
}

void Ship::setSegmentState(int numberOfCell, ShipCellState st) {
    state[numberOfCell] = st;
}

