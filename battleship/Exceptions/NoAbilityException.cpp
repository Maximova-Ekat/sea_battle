#include "NoAbilityException.h"

NoAbilityException::NoAbilityException(std::string message):
        message(message){}

std::string NoAbilityException::what() const noexcept
{
    std::string output = "No abilities available; "
                         "thrown exception with message: "+message;

    return output;
}