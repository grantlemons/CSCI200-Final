#include "GraphicalBoard.h"
#include <notcurses/notcurses.h>
#include <unistd.h>

GraphicalBoard::GraphicalBoard(notcurses *nc, const unsigned int Y,
                               const unsigned int X, const unsigned int ROWS,
                               const unsigned int COLS, const char **SYMBOLS) {
    this->_y = Y;
    this->_x = X;
    this->_rows = ROWS;
    this->_cols = COLS;
    this->_symbols = SYMBOLS;

    ncplane *std = notcurses_stdplane(nc);
    ncplane_options nopts = {
        (int)Y, (int)X, ROWS, COLS, NULL, NULL, NULL, 0, 0, 0,
    };
    this->_plane = ncplane_create(std, &nopts);
}
void GraphicalBoard::draw_board() {}
void GraphicalBoard::draw_x(const unsigned int INDEX) {}
void GraphicalBoard::draw_o(const unsigned int INDEX) {}
