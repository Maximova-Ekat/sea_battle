#ifndef BATTLESHIP_OUTOFFIELDATTACKEXCEPTION_H
#define BATTLESHIP_OUTOFFIELDATTACKEXCEPTION_H

#include "OutOfFieldAttackException.h"
#include <string>

class OutOfFieldAttackException
{
    std::pair<int, int> attackCoords;
    std::pair<int, int> fieldSize;
public:
    OutOfFieldAttackException(std::pair<int, int> attackCoords, std::pair<int, int> fieldSize);

    std::string what() const noexcept;
};


#endif //BATTLESHIP_OUTOFFIELDATTACKEXCEPTION_H
