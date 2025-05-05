#include "OutOfFieldAttackException.h"

#include <string>

OutOfFieldAttackException::OutOfFieldAttackException(std::pair<int, int> attackCoords, std::pair<int, int> fieldSize):
        attackCoords(attackCoords), fieldSize(fieldSize){}

std::string OutOfFieldAttackException::what() const noexcept
{
    std::string message = "Trying to attack ship at "+
            std::to_string(attackCoords.first) + "," + std::to_string(attackCoords.second)
              + " , while field size is " + std::to_string(fieldSize.first) + "," + std::to_string(fieldSize.second) + '\n';

    return message;
}