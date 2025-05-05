#include "ScannerInputManager.h"
#include <iostream>

std::pair<int, int> ScannerInputManager::getCoordinates() {
    int x, y;
    std::cout << "\"Enter coordinates for scanner as: <row> <column>\n";
    while(!(std::cin >> x >> y)){
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "Incorrect input. Repeat.\n";
        std::cout << "Enter coordinates as: <row> <column>\n";
    }
    return {x, y};
}
