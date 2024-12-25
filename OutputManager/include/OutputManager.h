#ifndef OUTPUTMANAGER_H
#define OUTPUTMANAGER_H

#include "Output.h"

template <typename OutputClass>
class OutputManager {
	OutputClass out;

public:

	OutputManager(OutputClass out) : out(out) {};

	void printMessage(std::string message) {
		out.printMessage(message);
	}

	void printField(std::pair<int, int> sizes, std::vector<std::vector<PlayingField::Condition>> field) {
		out.printField(sizes, field);
	}

	void printFieldIndex(std::pair<int, int> sizes, std::vector<std::vector<std::pair<int, int>>> field) {
		out.printFieldIndex(sizes, field);
	}

	void showField(PlayingField* player_field, PlayingField* bot_field) {
		out.showField(player_field, bot_field);
	}

	void help() {
		out.help();
	}

	~OutputManager() = default;
};

#endif