#ifndef BATTLESHIP_BOMBARDMENT_H
#define BATTLESHIP_BOMBARDMENT_H

#include "Ability.h"
#include "../InteractionManager.h"
#include <cstdlib>
#include <ctime>

class Bombardment : public Ability {
private:
    InteractionManager* manager;
public:
    Bombardment(void* manager);
    bool apply() override;
    std::string getName() const override {
        return "Bombardment";
    }
};


#endif //BATTLESHIP_BOMBARDMENT_H
