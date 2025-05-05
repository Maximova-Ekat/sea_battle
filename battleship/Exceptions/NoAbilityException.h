
#ifndef BATTLESHIP_NOABILITYEXCEPTION_H
#define BATTLESHIP_NOABILITYEXCEPTION_H


#include<string>

class NoAbilityException
{
    std::string message;
public:
    NoAbilityException(std::string message = "");

    std::string what() const noexcept;
};


#endif //BATTLESHIP_NOABILITYEXCEPTION_H
