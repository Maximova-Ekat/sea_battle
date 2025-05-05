#include "FieldCellState.h"
#include "../Ship/Ship.h"

#ifndef BATTLESHIP_CELL_H
#define BATTLESHIP_CELL_H

class Cell {
private:
    FieldCellState trueState;
    FieldCellState visibleState;
    Ship* ship;
    int shipCoords;
public:
    Cell();
    Cell(FieldCellState trueState, FieldCellState visibleState);
    FieldCellState getTrueState();
    FieldCellState getVisibleState();
    void setTrueState(FieldCellState state);
    void setShip(Ship& ship, int coords);
    void setVisibleState(FieldCellState state);
    Ship* getShip();
    int getShipCoords() const;
    ~Cell() = default;
};

#endif //BATTLESHIP_CELL_H
