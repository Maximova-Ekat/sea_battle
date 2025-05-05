#include "Ability.h"
#include "../InteractionManager.h"
#include <string>

#ifndef BATTLESHIP_DOUBLEDAMAGE_H
#define BATTLESHIP_DOUBLEDAMAGE_H

class DoubleDamage : public Ability {
private:
    InteractionManager* manager;

public:
    DoubleDamage(void* manager);
    bool apply() override;
    std::string getName() const override {
        return "Double Damage";
    }
};


#endif //BATTLESHIP_DOUBLEDAMAGE_H
