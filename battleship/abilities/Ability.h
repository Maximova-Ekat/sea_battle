#ifndef BATTLESHIP_ABILITY_H
#define BATTLESHIP_ABILITY_H

#include <utility>
#include <string>

class Ability {
public:
    virtual bool apply() = 0;
    virtual ~Ability() = default;
    virtual std::string getName() const = 0;
};

#endif //BATTLESHIP_ABILITY_H
