#include "Cell.h"

Cell::Cell() {
    trueState = FieldCellState::Empty;
    visibleState = FieldCellState::Unknown;
}

FieldCellState Cell::getTrueState() {
    return trueState;
}

FieldCellState Cell::getVisibleState() {
    return visibleState;
}

void Cell::setTrueState(FieldCellState state) {
    trueState = state;
}

void Cell::setVisibleState(FieldCellState state) {
    visibleState = state;
}

Cell::Cell(FieldCellState trueState, FieldCellState visibleState) {
    this->trueState = trueState;
    this->visibleState = visibleState;
}

void Cell::setShip(Ship &ship, int coords) {
    this->ship = &ship;
    shipCoords = coords;
}

Ship *Cell::getShip() {
    return ship;
}

int Cell::getShipCoords() const {
    return shipCoords;
}