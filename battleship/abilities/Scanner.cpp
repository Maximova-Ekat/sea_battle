#include <iostream>
#include "Scanner.h"

Scanner::Scanner(void* manager){
    this->manager = ((InteractionManager*)manager);

}

bool Scanner::apply() {
    bool foundShip = false;
    auto coords = ScannerInputManager::getCoordinates();
    for (int i = coords.first; i < coords.first + 2; ++i) {
        for (int j = coords.second; j < coords.second + 2; ++j) {
            if (manager->getField()->isCoordinatesInField({i, j}) &&
                manager->getField()->getCellTrueState({i, j}) == FieldCellState::Ship) {
                foundShip = true;
                break;
            }
        }
        if (foundShip) break;
    }
    if (foundShip) {
        std::cout << "Ship is found\n";
    } else {
        std::cout << "not found\n";
    }
    return foundShip;
}