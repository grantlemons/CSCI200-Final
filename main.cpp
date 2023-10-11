#include "Board.h"
#include "LeafBoard.h"
#include "PrimaryBoard.h"
#include "Shared.cpp"

#include <optional>
#include <iostream>
using namespace std;

int main() {
    PrimaryBoard pBoard = PrimaryBoard();
    LeafBoard *selectedLeafBoard = nullptr;

    optional<LeafBoard *> optBoard = pBoard.select_board(4);
    if (optBoard != nullopt) {
        selectedLeafBoard = optBoard.value();
    }

    selectedLeafBoard->set_cell_owner(0, Player1);
    selectedLeafBoard->set_cell_owner(1, Player1);
    selectedLeafBoard->set_cell_owner(2, Player1);

    cout << selectedLeafBoard->winner << endl;

    return EXIT_SUCCESS;
}
