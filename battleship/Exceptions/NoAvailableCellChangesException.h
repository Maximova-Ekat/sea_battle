//
// Created by katyusha on 26.11.24.
//

#ifndef BATTLESHIP_NOAVAILABLECELLCHANGESEXCEPTION_H
#define BATTLESHIP_NOAVAILABLECELLCHANGESEXCEPTION_H

#include <string>

class NoAvailableCellChangesException
{
    std::pair<int, int> attackCoords;

public:
    explicit NoAvailableCellChangesException(std::pair<int, int> attackCoords);
    std::string what() const noexcept;
};


#endif //BATTLESHIP_NOAVAILABLECELLCHANGESEXCEPTION_H
