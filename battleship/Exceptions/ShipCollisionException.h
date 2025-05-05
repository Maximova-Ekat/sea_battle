//
// Created by katyusha on 06.11.24.
//

#ifndef BATTLESHIP_SHIPCOLLISIONEXCEPTION_H
#define BATTLESHIP_SHIPCOLLISIONEXCEPTION_H



#include <string>

class ShipCollisionException
{
    std::pair<int, int> shipCoords;
    std::string message = "";
public:
    ShipCollisionException(std::pair<int, int> coords, std::string message = "");
    std::string what() const noexcept;
};

#endif //BATTLESHIP_SHIPCOLLISIONEXCEPTION_H
