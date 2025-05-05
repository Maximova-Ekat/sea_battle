#include "Bombardment.h"

Bombardment::Bombardment(void* manager){
    this->manager = ((InteractionManager*)manager);
}

bool Bombardment::apply() {
    srand(time(nullptr));
    if (manager->getShipsManager()->getCount() > 0) {
        Ship* target_ship = nullptr;
        int random_index;

        do {
            random_index = rand() % manager->getShipsManager()->getCount();
            target_ship = manager->getShipsManager()->getShips()[random_index];
        } while(target_ship->isDestroyed());

        int segment_index;
        do {
            segment_index = rand() % target_ship->getLength();
        } while(target_ship->getSegmentState(segment_index) == ShipCellState::Destroyed);

        target_ship->changeState(segment_index);
    }
    return true;
}
