// FieldPrinter.h

#ifndef BATTLESHIP_FIELDPPRINTER_H
#define BATTLESHIP_FIELDPPRINTER_H

#include "Field/Field.h"
#include <iostream>

class FieldPrinter {
private:
    Field* field;

public:
    FieldPrinter(Field* field);
    void print(bool user) const;
};

#endif //BATTLESHIP_FIELDPPRINTER_H