#include "Board.h"
#include "GraphicalBoard.h"
#include "NcHandler.h"
#include "LeafBoard.h"
#include "PrimaryBoard.h"
#include "Shared.h"

#include <memory>
#include <optional>
using namespace std;

int main() {
    shared_ptr<NcHandler> ncHandler(new NcHandler());
    ncplane *std = ncHandler->get_stdplane();

    const int ROWS = (3 * 11) + 2;
    const int COLS = (3 * 20) + 2;

    unsigned int std_rows, std_cols;
    std_rows = std_cols = 0;
    ncplane_dim_yx(std, &std_rows, &std_cols);

    unsigned int std_center_y, std_center_x;
    std_center_y = std_rows / 2;
    std_center_x = std_cols / 2;

    int board_origin_y, board_origin_x;
    board_origin_y = std_center_y - (ROWS / 2);
    board_origin_x = std_center_x - (COLS / 2);

    ncplane_options nopts = {
        board_origin_y, board_origin_x, ROWS, COLS, NULL, NULL, NULL, 0, 0, 0,
    };

    const char *THICK_SYMBOLS[3] = {"\u2501", "\u2503", "\u254B"};
    const uint64_t THICK_CHANNELS = ncplane_channels(std);

    GraphicalBoard gboard(ncHandler, nopts, THICK_CHANNELS, THICK_SYMBOLS);
    gboard.draw_board();

    return EXIT_SUCCESS;
}
