// #include "tui.h"

#include <clocale>
#include <notcurses/notcurses.h>

#include <unistd.h>
#include <string>
#include <vector>

int draw_board_yx(ncplane *p, const int y, const int x,
                  const unsigned int ROWS_PER_BCELL,
                  const unsigned int COLS_PER_BCELL, const char **SYMBOLS,
                  const uint64_t CELL_CHANNELS) {
    int res = EXIT_SUCCESS;

    // calculate lines positions and lengths
    const unsigned int H_IDX_1 = y + ROWS_PER_BCELL;
    const unsigned int H_IDX_2 = y + (2 * ROWS_PER_BCELL);

    const unsigned int V_IDX_1 = x + COLS_PER_BCELL;
    const unsigned int V_IDX_2 = x + (2 * COLS_PER_BCELL);

    const unsigned int H_LINE_LEN = (3 * COLS_PER_BCELL) + 1;
    const unsigned int V_LINE_LEN = (3 * ROWS_PER_BCELL) + 1;

    // define cells
    nccell HORI_CELL, VERT_CELL, JUNC_CELL;
    nccell_load(p, &HORI_CELL, SYMBOLS[0]);
    nccell_load(p, &VERT_CELL, SYMBOLS[1]);
    nccell_load(p, &JUNC_CELL, SYMBOLS[2]);
    nccell_set_channels(&HORI_CELL, CELL_CHANNELS);
    nccell_set_channels(&VERT_CELL, CELL_CHANNELS);
    nccell_set_channels(&JUNC_CELL, CELL_CHANNELS);

    // draw horizontal lines
    res |= ncplane_cursor_move_yx(p, H_IDX_1, x);
    res |= ncplane_hline(p, &HORI_CELL, H_LINE_LEN);

    res |= ncplane_cursor_move_yx(p, H_IDX_2, x);
    res |= ncplane_hline(p, &HORI_CELL, H_LINE_LEN);

    // draw vertical lines
    res |= ncplane_cursor_move_yx(p, y, V_IDX_1);
    res |= ncplane_vline(p, &VERT_CELL, V_LINE_LEN);

    res |= ncplane_cursor_move_yx(p, y, V_IDX_2);
    res |= ncplane_vline(p, &VERT_CELL, V_LINE_LEN);

    // draw junction points
    res |= ncplane_putc_yx(p, H_IDX_1, V_IDX_1, &JUNC_CELL);
    res |= ncplane_putc_yx(p, H_IDX_1, V_IDX_2, &JUNC_CELL);

    res |= ncplane_putc_yx(p, H_IDX_2, V_IDX_1, &JUNC_CELL);
    res |= ncplane_putc_yx(p, H_IDX_2, V_IDX_2, &JUNC_CELL);

    return res;
}

void init_boards(notcurses *nc, ncplane *pBoard, ncplane *lBoards[9]) {
    ncplane *std = notcurses_stdplane(nc);

    const int ROWS = (3 * 11) + 2;
    const int COLS = (3 * 20) + 2;

    unsigned int std_rows, std_cols;
    ncplane_dim_yx(std, &std_rows, &std_cols);

    unsigned int std_center_y, std_center_x;
    std_center_y = std_rows / 2;
    std_center_x = std_cols / 2;

    int board_origin_y, board_origin_x;
    board_origin_y = std_center_y - (ROWS / 2);
    board_origin_x = std_center_x - (COLS / 2);

    ncplane_options nopts = {
        board_origin_y, board_origin_x, ROWS, COLS, NULL,
        "nc_pBoard",    NULL,           0,    0,    0,
    };

    pBoard = ncplane_create(std, &nopts);

    // draw primary board
    const char *THICK_SYMBOLS[3] = {"\u2501", "\u2503", "\u254B"};
    const uint64_t DEFAULT_CHANNELS = ncplane_channels(pBoard);
    draw_board_yx(pBoard, 0, 0, 11, 20, THICK_SYMBOLS, DEFAULT_CHANNELS);

    const uint32_t THIN_FG_CHANNEL = NCCHANNEL_INITIALIZER(0x77, 0x77, 0x77);
    const uint32_t THIN_BG_CHANNEL = ncplane_bchannel(pBoard);
    const uint64_t THIN_CHANNELS =
        ((uint64_t)THIN_FG_CHANNEL << 32ull) + THIN_BG_CHANNEL;
    const char *THIN_SYMBOLS[3] = {"\u2500", "\u2502", "\u253C"};

    // draw leaf boards
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            ncplane_options lBoardOpts = {
                (i * 11) + 1, (j * 20) + 1, 11, 20, NULL, NULL, NULL, 0, 0, 0};
            ncplane *leafBoard = ncplane_create(pBoard, &lBoardOpts);
            draw_board_yx(leafBoard, 0, 0, 3, 6, THIN_SYMBOLS, THIN_CHANNELS);
            lBoards[(i * 3) + j] = leafBoard;
        }
    }

    notcurses_render(nc);
}

int main(void) {
    setlocale(LC_ALL, "");
    notcurses *nc = notcurses_init(NULL, NULL);

    ncplane *pBoard = nullptr, *lBoards[9];
    init_boards(nc, pBoard, lBoards);

    for (ncplane *b : lBoards) {
        ncplane_erase(b);
        sleep(1);
        notcurses_render(nc);
    }

    while (true) {
    }

    notcurses_stop(nc);

    return EXIT_SUCCESS;
}
