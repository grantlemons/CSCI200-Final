#include "Board.h"
#include "LeafBoard.h"
#include "PrimaryBoard.h"
#include "Shared.h"

#include <optional>
#include <iostream>
using namespace std;

int main() {
    PrimaryBoard *pBoard = new PrimaryBoard();
    LeafBoard *selectedLeafBoard;

    optional<LeafBoard *> optBoard = pBoard->select_board(4);
    if (optBoard != nullopt) {
        selectedLeafBoard = optBoard.value();
    }

    selectedLeafBoard->set_cell_owner(0, Player1);
    selectedLeafBoard->set_cell_owner(1, Player1);
    selectedLeafBoard->set_cell_owner(3, Player1);

    print_owner(selectedLeafBoard->winner);

    return EXIT_SUCCESS;
}
