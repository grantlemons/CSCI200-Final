#include <cmath>
#include <ostream>

#include "Shared.h"

std::ostream &operator<<(std::ostream &out, const CellOwner OWNER) {
    if (OWNER == None) {
        return out << "N";
    } else if (OWNER == Player1) {
        return out << "1";
    } else if (OWNER == Player2) {
        return out << "2";
    } else {
        return out << "Unknown CellOwner Variant";
    }
}

unsigned int negative_mod(int a, int b) {
    return a - (b * floor((double)a / b));
}

void horizontal_others(const int INDEX, int &other1, int &other2) {
    other1 = negative_mod(INDEX - 1, 3);
    other2 = (INDEX + 1) % 3;
}
void vertical_others(const int INDEX, int &other1, int &other2) {
    other1 = negative_mod(INDEX - 3, 9);
    other2 = (INDEX + 3) % 9;
}
void diagonal_fours_others(const int INDEX, int &other1, int &other2) {
    other1 = negative_mod(INDEX - 4, 12);
    other2 = (INDEX + 4) % 12;
}
void diagonal_twos_others(const int INDEX, int &other1, int &other2) {
    other1 = negative_mod(INDEX - 2, 10);
    other2 = (INDEX + 2) % 10;
}
