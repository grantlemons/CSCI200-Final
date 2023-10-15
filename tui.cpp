// #include "tui.h"

#include <clocale>
#include <notcurses/notcurses.h>

#include <unistd.h>

int draw_board(ncplane *p, const unsigned int ROWS_PER_BCELL,
               const unsigned int COLS_PER_BCELL) {
    int res = EXIT_SUCCESS;

    // calculate lines positions and lengths
    const unsigned int H_IDX_1 = ROWS_PER_BCELL;
    const unsigned int H_IDX_2 = 2 * ROWS_PER_BCELL;

    const unsigned int V_IDX_1 = COLS_PER_BCELL;
    const unsigned int V_IDX_2 = 2 * COLS_PER_BCELL;

    const unsigned int H_LINE_LEN = (3 * COLS_PER_BCELL) + 1;
    const unsigned int V_LINE_LEN = (3 * ROWS_PER_BCELL) + 1;

    // define cells
    nccell HORI_CELL, VERT_CELL, JUNC_CELL;
    nccell_load(p, &HORI_CELL, "\u2501");
    nccell_load(p, &VERT_CELL, "\u2503");
    nccell_load(p, &JUNC_CELL, "\u254B");
    nccell_set_bg_default(&HORI_CELL);
    nccell_set_fg_default(&HORI_CELL);
    nccell_set_bg_default(&VERT_CELL);
    nccell_set_fg_default(&VERT_CELL);
    nccell_set_bg_default(&JUNC_CELL);
    nccell_set_fg_default(&JUNC_CELL);

    // draw horizontal lines
    res |= ncplane_cursor_move_yx(p, H_IDX_1, 0);
    res |= ncplane_hline(p, &HORI_CELL, H_LINE_LEN);

    res |= ncplane_cursor_move_yx(p, H_IDX_2, 0);
    res |= ncplane_hline(p, &HORI_CELL, H_LINE_LEN);

    // draw vertical lines
    res |= ncplane_cursor_move_yx(p, 0, V_IDX_1);
    res |= ncplane_vline(p, &VERT_CELL, V_LINE_LEN);

    res |= ncplane_cursor_move_yx(p, 0, V_IDX_2);
    res |= ncplane_vline(p, &VERT_CELL, V_LINE_LEN);

    // draw junction points
    res |= ncplane_putc_yx(p, H_IDX_1, V_IDX_1, &JUNC_CELL);
    res |= ncplane_putc_yx(p, H_IDX_1, V_IDX_2, &JUNC_CELL);

    res |= ncplane_putc_yx(p, H_IDX_2, V_IDX_1, &JUNC_CELL);
    res |= ncplane_putc_yx(p, H_IDX_2, V_IDX_2, &JUNC_CELL);

    return res;
}

int main(void) {
    setlocale(LC_ALL, "");

    notcurses *nc = notcurses_init(NULL, NULL);
    ncplane *p = notcurses_stdplane(nc);

    const int ROWS = 17 * 3;
    const int COLS = 32 * 3;

    unsigned int std_rows, std_cols;
    ncplane_dim_yx(p, &std_rows, &std_cols);

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

    ncplane *n = ncplane_create(p, &nopts);
    draw_board(n, 15, 30);

    notcurses_render(nc);

    while (true) {
    }

    notcurses_stop(nc);

    return EXIT_SUCCESS;
}
