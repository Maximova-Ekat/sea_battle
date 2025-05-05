#include "DoubleDamage.h"

DoubleDamage::DoubleDamage(void* manager){
    this->manager = ((InteractionManager*)manager);
}

bool DoubleDamage::apply() {
    manager->applyDoubleDamage();
    return true;
}