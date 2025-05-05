// FieldPrinter.cpp

#include "FieldPrinter.h"

FieldPrinter::FieldPrinter(Field* field) : field(field) {}

void FieldPrinter::print(bool user) const {
    int height = field->getHeight();
    int width = field->getWidth();
    // Print header
    std::cout << "  ";
    for (int j = 0; j < width; ++j) {
        std::cout << j << " ";
    }
    std::cout << '\n';
    for (int i = 0; i < height; ++i) {
        std::cout << i << " "; // Print row index
        for (int j = 0; j < width; ++j) {
            Cell* cell = field->getCells()[i][j];
            FieldCellState visibleState;
            if (user) {
                visibleState = cell->getTrueState();
            } else {
                visibleState = cell->getVisibleState();
            }

            switch (visibleState) {
                case FieldCellState::Unknown:
                    std::cout << "\033[0;37m? \033[0m"; // White for unknown
                    break;
                case FieldCellState::Empty:
                    std::cout << "\033[0;34m. \033[0m"; // Blue for empty
                    break;
                case FieldCellState::Ship:
                    // Check ship segment state

                    if (cell->getShip()->getSegmentState({i, j}) == ShipCellState::Destroyed) {
                        std::cout << "\033[0;31mX \033[0m"; // Red
                    }
                    if (cell->getShip()->getSegmentState({i, j}) == ShipCellState::Damaged) {
                        std::cout << "\033[0;33mD \033[0m"; // Yellow
                    }
                    if (cell->getShip()->getSegmentState({i, j}) == ShipCellState::Whole) {
                        std::cout << "\033[0;32mS \033[0m"; // Green
                    }

                    break;
            }
        }
        std::cout << std::endl;
    }
}