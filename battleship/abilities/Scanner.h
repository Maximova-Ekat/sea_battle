#include "Ability.h"
#include "../InteractionManager.h"
#include "ScannerInputManager.h"
#include <cstdlib>

#ifndef BATTLESHIP_SCANNER_H
#define BATTLESHIP_SCANNER_H

class Scanner : public Ability {
private:
    InteractionManager* manager;
public:
    Scanner(void* manager);
    bool apply() override;
    std::string getName() const override {
        return "Scanner";
    }
};

#endif //BATTLESHIP_SCANNER_H