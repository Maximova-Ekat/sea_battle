#include "Game.h"
#include "Exceptions/ShipCollisionException.h"
#include "Exceptions/NoAbilityException.h"
#include "Exceptions/OutOfFieldAttackException.h"
#include "Exceptions/NoAvailableCellChangesException.h"
#include <iostream>

Game::Game() {
    state = new GameState("../save.json");
    myField = new Field(1,1);
    myShips = new ShipsManager(0, nullptr);
    manager = new InteractionManager(1,1,0,nullptr);
}

Game::~Game() {
    delete manager;
    delete myField;
    delete myShips;
}

int Game::getValidInput(const std::string& prompt, int minValue, int maxValue) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < minValue || value > maxValue) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод. Пожалуйста, введите значение между " << minValue << " и " << maxValue << ".\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    return value;

}

void Game::startNewGame() {
    if(isStarted) return;
    isStarted = true;
    auto sizes = setField();
    auto ships = setupShipsManager();
    delete manager;
    manager = new InteractionManager(sizes.first, sizes.second, ships.first, ships.second);
    placeUserShips();
    placeEnemyShips();
    turn(1);
}


std::pair<int, int> Game::setField() {
    int x, y;
    std::cout << "Enter coordinates for field as: <row> <column>\n";
    while(!(std::cin >> x >> y) || x <= 0 || y <= 0 || x > 20 || y > 20) {
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "Invalid input detected. Repeat.\n";
        std::cout << "Enter coordinates as: <row> <column>\n";
    }
    delete myField;
    myField = new Field(x, y);
    return {x, y};
}


std::pair<int, int*> Game::setupShipsManager() {
    int shipCount = getValidInput("Введите количество кораблей: ", 1, std::min(myField->getHeight()/2 + 1, 11));
    int *shipSizes = new int[shipCount];
    for (int i = 0; i < shipCount; ++i) {
        shipSizes[i] = getValidInput("Введите размер корабля " + std::to_string(i + 1) + " (1-4): ", 1, std::min(myField->getHeight(), 4));
    }
    delete myShips;
    myShips = new ShipsManager(shipCount, shipSizes);
    return {shipCount, shipSizes};
}

void Game::placeUserShips() {
    for (int i = 0; i < myShips->getCount(); ++i) {
        Ship& ship = myShips->getShip(i);
        bool placed = false;
        while (!placed) {
            std::string orientationInput;
            Orientation orientation;
            std::cout << "Enter coordinates for ship " << i + 1 << '\n';
            int x = getValidInput("enter x:", 0, myField->getHeight()-1);
            int y = getValidInput("enter y:", 0, myField->getWidth()-1);
            std::cout << "Enter orientation for ship " << i + 1 << " (H for horizontal, V for vertical): ";
            std::cin >> orientationInput;
            if (orientationInput == "H" || orientationInput == "h") {
                orientation = Orientation::Horizontal;
            } else if (orientationInput == "V" || orientationInput == "v") {
                orientation = Orientation::Vertical;
            } else {
                std::cout << "Invalid orientation. Please enter 'H' or 'V'." << std::endl;
                continue;
            }
            try {
                myField->setShip(ship, {x, y}, orientation);
                placed = true;
                std::cout << "Ship " << i + 1 << " placed successfully at (" << x << ", " << y << ") facing " << orientationInput << "." << std::endl;
            }catch(const ShipCollisionException& e) {
                std::cout << e.what() << '\n';
            }
        }
    }

}

void Game::placeEnemyShips() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, myField->getHeight() - 1);
    std::uniform_int_distribution<> disWidth(0, myField->getWidth() - 1);

    for (int i = 0; i < manager->shipsManager->getCount(); ++i) {
        Ship& ship = manager->shipsManager->getShip(i);
        bool placed = false;

        while (!placed) {
            int x = dis(gen);
            int y = disWidth(gen);
            Orientation orientation = (dis(gen) % 2 == 0) ? Orientation::Horizontal : Orientation::Vertical;
            try {
                manager->gamefield->setShip(ship, {x, y}, orientation);
                placed = true;
                std::cout << "Enemy ship " << i + 1 << " placed at (" << x << ", " << y << ") facing " << (orientation == Orientation::Horizontal ? "H" : "V") << "." << std::endl;
            } catch (const ShipCollisionException& e) {
                //std::cout << e.what() << '\n'; // Можно закомментировать, чтобы не выводить сообщения при каждой неудаче
            }
        }
    }
}

void Game::attack(std::pair<int, int> coords) {
    if(!isStarted) return;
    manager->attack(coords);
}

bool Game::useAbility() {
    if(isStarted) {
        bool res = manager->apply();
        return res;
    }
}

void Game::userTurn() {
    manager->getAbilityManager()->printAbilities();
    char use;
    std::cout << "Do you want to use an ability? (y/n): ";
    std::cin >> use;
    if (use == 'y' || use == 'Y') {
        try {
            bool result = useAbility();
            std::cout << "If you used Scanner,the result shows, if ship is found. In other cases 1 means ability applied\n";
            std::cout << "Result of the ability: " << result << '\n';
        } catch (const NoAbilityException& e) {
            std::cout << e.what();
        }
    } else {
        std::cout << "You chose not to use an ability.\n";
    }
    while (true){
        int x = getValidInput("enter x:", 0, myField->getHeight()-1);
        int y = getValidInput("enter y:", 0, myField->getWidth()-1);
        try {
            attack({x, y});
            break;
        } catch (const OutOfFieldAttackException& e) {
            std::cout << e.what();
        } catch (const NoAvailableCellChangesException& e) {
            std::cout << e.what();
        }
    }
}

void Game::turn(bool isUserTurn) {
    while (myShips->allDestroyed() == false && (manager->shipsManager->allDestroyed() == false)) {
        if (isUserTurn) {
            std::cout << "Enter 'e' to finish the game\n";
            std::cout << "Enter 's' to saving the game\n";
            char use;
            std::cin >> use;
            if (use == 'e') {
                std::cout << "The game is over\n";
                exitGame();
            } else if(use == 's'){
                saveGame();
                std::cout << "The game has been saved successfully\n";
            }
            userTurn();
            FieldPrinter printer2(manager->gamefield);
            printer2.print(1);
        } else {
            compAttack();
            FieldPrinter printer1(myField);
            printer1.print(1);
        }

        isUserTurn = !isUserTurn;
    }

    stopOrContinue(myShips->allDestroyed(), manager->shipsManager->allDestroyed());
}

void Game::stopOrContinue(bool userShipsAreDestroyed, bool enemyShipsAreDestroyed) {
    string question;
    if (enemyShipsAreDestroyed == true) {
        std::cout << "You've won!\n";
        std::cout << "Do you want to continue playing? If yes, write 'yes', otherwise 'no'\n";
        std::string question;
        std::cin >> question;
        if (question == "yes") {
            manager->generateNewEnemy(myField->getHeight(), myField->getWidth());
            placeEnemyShips();
            turn(1);
        }
        else if (question == "no") {
            exitGame();
        }
    }
    else if (userShipsAreDestroyed == true) {
        std::cout << "You've lost!\n";
        std:: cout << "Do you want to get back at the bot? If yes, write 'yes', otherwise 'no'\n";
        std::string question;
        std::cin >> question;
        if (question == "yes") {
            std::cout << "Enter the size of the field: \n";
            startNewGame();
        }
        else if (question == "no") {
            exitGame();
        }
    }
}

void Game::exitGame() {
    isExit = true;
    std::cout << "The game is over!\n";
    exit(0);
}

void Game::saveGame() {
    if(!isStarted) return;
    state->saving(myField,myShips,manager);
}

void Game::loadGame() {
    state->loading(myField,myShips,manager);
    isStarted = true;
    turn(1);
}

void Game::compAttack() {
    if(!isStarted) return;
    int x = rand() % myField->getHeight();
    int y = rand() % myField->getWidth();
    try {
        myField->attack({x,y});
    } catch (const NoAvailableCellChangesException& e) {
        std::cout << e.what();
    }
}

void Game::play() {
    if(state->is_file_written()) {
        std::cout << "Play the Sea Battle game!\n";
        std::cout << "Would you like to load a saved game? Type 'y' to proceed\n";
        std::string answer;
        std::cin >> answer;
        if(answer == "y") {
            loadGame();
        } else {
            startNewGame();
        }
    } else {
        startNewGame();
    }
}
