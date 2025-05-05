#include "ShipCellState.h"
#include "Orientation.h"
#ifndef BATTLESHIP_SHIP_H
#define BATTLESHIP_SHIP_H
#include <utility>

class Ship {
private:
    std::pair<int, int> coordinates;
    int len;
    Orientation orientation;
    ShipCellState state[4];

public:
    Ship(int len);
    int getLength() const;
    std::pair<int, int> getCoordinates();
    Orientation getOrientation();
    ShipCellState getSegmentState(int numberOfCell);
    void setSegmentState(int numberOfCell, ShipCellState st);
    std::pair<int, int> getSegmentCoordinates(int numberOfCell);
    void setCoordinates(std::pair<int, int> coords);
    void setOrientation(Orientation orient);
    void changeState(int numberOfCell);
    void destroySegment(int numberOfCell);
    bool isDestroyed();
    ~Ship() = default;
    void print();
    ShipCellState getSegmentState(std::pair<int, int> point);
};


#endif