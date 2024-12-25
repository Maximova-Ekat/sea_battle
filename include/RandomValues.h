#ifndef RANDOMVALUES_H
#define RANDOMVALUES_H

#include <iostream>
#include <random>
#include <ctime>

class RandomValues {
public:
	RandomValues();

	std::pair<int, int> getRandomCoordinates(std::pair <int, int> sizes);

	~RandomValues() = default;
};


#endif