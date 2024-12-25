#include "RandomValues.h"

RandomValues::RandomValues() {
}

std::pair<int, int> RandomValues::getRandomCoordinates(std::pair<int, int> sizes) {
	std::pair <int, int> coordinates;
	coordinates.second = rand() % (sizes.second) + 1;
	coordinates.first = rand() % (sizes.first) + 1;
	return coordinates;
}