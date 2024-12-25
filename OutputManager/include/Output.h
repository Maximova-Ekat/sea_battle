#ifndef OUTPUT_H
#define OUTPUT_H

#include <ostream>
#include <sstream>
#include "../include/PlayingField.h"

class Output{
private:
	std::ostream& os;

	char conditionToChar(PlayingField::Condition symbol);

public:
	Output(std::ostream& os) : os(os) {};

	void printMessage(std::string message);

	void printField(std::pair<int, int> sizes, std::vector<std::vector<PlayingField::Condition>> field);

	void printFieldTwo(std::pair<int, int> sizes, std::vector<std::vector<PlayingField::Condition>> player_field, std::vector<std::vector<PlayingField::Condition>> bot_field);

	void printFieldIndex(std::pair<int, int> sizes, std::vector<std::vector<std::pair<int, int>>> field);

	void showField(PlayingField* player_field, PlayingField* bot_field);

	void help();

	~Output() = default;
};

#endif