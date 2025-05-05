cmake_minimum_required(VERSION 3.27.8)
project(battleship)

set(CMAKE_CXX_STANDARD 17)

add_executable(battleship main.cpp
        Ship/Ship.cpp
        Ship/Ship.h
        Ship/Ship.h
        Ship/Ship.h
        Ship/Ship.cpp
        Ship/ShipCellState.h
        Ship/ShipCellState.h
        Ship/ShipCellState.h
        Ship/Orientation.h
        Field/Field.cpp
        Field/Field.h
        Field/Cell.cpp
        Field/Cell.h
        Field/FieldCellState.h
        ShipsManager.cpp
        ShipsManager.h
        ShipsManager.h
        abilities/Ability.h
        abilities/Scanner.cpp
        abilities/Scanner.h
        abilities/Scanner.h
        abilities/DoubleDamage.cpp
        abilities/DoubleDamage.h
        abilities/Bombardment.cpp
        abilities/Bombardment.h
        AbilityManager.cpp
        AbilityManager.h
        InteractionManager.cpp
        InteractionManager.h
        Exceptions/NoAbilityException.cpp
        Exceptions/NoAbilityException.h
        Exceptions/NoAbilityException.h
        Exceptions/ShipCollisionException.cpp
        Exceptions/ShipCollisionException.h
        Exceptions/OutOfFieldAttackException.cpp
        Exceptions/OutOfFieldAttackException.h
        abilities/ScannerInputManager.cpp
        abilities/ScannerInputManager.h
        Game.cpp
        Game.h
        GameState.cpp
        GameState.h
        InteractionWithFile.cpp
        InteractionWithFile.h
        Exceptions/NoAvailableCellChangesException.cpp
        Exceptions/NoAvailableCellChangesException.h
        Exceptions/NoAvailableCellChangesException.h
        FieldPrinter.cpp
        FieldPrinter.h
        FieldPrinter.h
)
