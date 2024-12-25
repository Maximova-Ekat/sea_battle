#ifndef PLAYINGFIELD_H
#define PLAYINGFIELD_H

#include <iostream>
#include <vector>
#include <utility>
#include <iomanip>
#include "Warship.h"


class PlayingField {
public:
	enum Condition {
		unknown,
		hide,
		damaged,
		destroyed,
		empty
	};

private:
	std::vector <std::vector <Condition>> field_view;
	std::vector <std::vector <std::pair<int, int>>> field_value;
	int height;
	int width;

	void createField();

	bool checkNeighbors(int length, int x, int y, bool orientation);

	bool checkCorrect(int length, int x, int y, bool orientation);

	std::string conditionToString(Condition condition) const;

	Condition stringToCondition(const std::string str);

public:
	PlayingField(int width, int height);

	PlayingField();

	PlayingField(const PlayingField& other);

	PlayingField(PlayingField&& other) noexcept;

	PlayingField& operator=(const PlayingField& other);

	PlayingField& operator=(PlayingField&& other) noexcept;

	json to_json() const;

	void from_json(const json& j);

	std::pair <int, int> getSize();

	bool setShip(Warship* ship, int x, int y, bool orientation, int value);

	int cellAtack(int x, int y, bool is_hide = false);

	void killDeck(int x, int y);

	int getDeckIndex(int x, int y);

	std::vector<std::vector<Condition>> getView();

	std::vector<std::vector<std::pair<int, int>>> getViewIndex();

	~PlayingField();

};


#endif