#ifndef BATTLESHIP_SCANNERINPUTMANAGER_H
#define BATTLESHIP_SCANNERINPUTMANAGER_H
#include <utility>

class ScannerInputManager {
public:
    static std::pair<int,int> getCoordinates();
    ~ScannerInputManager() = default;
};


#endif //BATTLESHIP_SCANNERINPUTMANAGER_H
