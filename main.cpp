#include "Board.h"
#include "LeafBoard.h"
#include "PrimaryBoard.h"
#include "Shared.h"

#include <optional>
#include <iostream>
using namespace std;

int choose_board(const CellOwner PLAYER) {
    int res;
    cout << PLAYER << ": Enter outer cell: ";
    cin >> res;

    return res;
}

int main() {
    PrimaryBoard *pBoard = new PrimaryBoard();
    optional<LeafBoard *> optBoard;
    LeafBoard *selectedLeafBoard;

    cout << *pBoard << endl;

    CellOwner player = Player1;
    int index = choose_board(player);

    do {
        while (pBoard->get_cell_owner(index) != None) {
            cout << "Cell is already owned!" << endl;
            index = choose_board(player);
        }
        optBoard = pBoard->select_board(index);
        if (optBoard != nullopt) {
            selectedLeafBoard = optBoard.value();
        }

        cout << *selectedLeafBoard << endl;
        cout << player << ": Enter inner cell: ";
        cin >> index;
        while (!selectedLeafBoard->set_cell_owner(index, player)) {
            cout << "Cell is already owned!" << endl;
            cout << player << ": Enter inner cell: ";
            cin >> index;
        }

        if (player == Player1)
            player = Player2;
        else {
            player = Player1;
        }
        cout << *pBoard << endl;
    } while (!pBoard->check_win(index, player));

    return EXIT_SUCCESS;
}
