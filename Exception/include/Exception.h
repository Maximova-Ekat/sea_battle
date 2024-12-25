#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

class InputSizeException{
public:
	InputSizeException() = default;
	std::string what();
};

class InputValueException {
public:
	InputValueException() = default;
	std::string what();	
};

class InputCoordinatesException {
public:
	InputCoordinatesException() = default;
	std::string what();
};

class InputCoordAndOrientException {
public:
	InputCoordAndOrientException() = default;
	std::string what();
};

class SetShipException {
public:
	SetShipException() = default;
	std::string what();
};

class UseAbilityException {
public:
	UseAbilityException() = default;
	std::string what();
};

class RandomSetShipException {
public:
	RandomSetShipException() = default;
};

class OpenFileException {
public:
	OpenFileException() = default;
	std::string what();
};

class UnknownCommandException {
public:
	UnknownCommandException() = default;
	std::string what();
};

class AttackCommandException {
public:
	AttackCommandException() = default;
	std::string what();
};

class UseAbilityCommandException {
public:
	UseAbilityCommandException() = default;
	std::string what();
};

class SaveCommandException {
public:
	SaveCommandException() = default;
	std::string what();
};
#endif