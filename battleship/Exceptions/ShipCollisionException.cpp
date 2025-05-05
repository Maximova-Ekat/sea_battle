#include "ShipCollisionException.h"

ShipCollisionException::ShipCollisionException(std::pair<int, int> coords, std::string message):
        shipCoords(coords), message(message){}

std::string ShipCollisionException::what() const noexcept
{
    std::string output = "Error at ship placement occured: "
                         " trying to put ship at " + std::to_string(shipCoords.first) + "," + std::to_string(shipCoords.second);
    if(!message.empty())
        output+=" with message: " + message;
    output+='\n';
    return output;
}