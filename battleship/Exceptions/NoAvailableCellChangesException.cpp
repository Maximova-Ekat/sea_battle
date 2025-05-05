//
// Created by katyusha on 26.11.24.
//

#include "NoAvailableCellChangesException.h"


NoAvailableCellChangesException::NoAvailableCellChangesException(std::pair<int, int> attackCoords):
        attackCoords(attackCoords){}

std::string NoAvailableCellChangesException::what() const noexcept {
    std::string message = "You had already attacked at"+
                          std::to_string(attackCoords.first) + "," + std::to_string(attackCoords.second)
                          +  '\n';
    return message;
}