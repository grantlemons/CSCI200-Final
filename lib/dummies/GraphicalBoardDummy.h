#ifndef G_BOARD_DUMMY
#define G_BOARD_DUMMY

#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/interfaces/GraphicalAreaI.h"
#include "lib/interfaces/GraphicalBoardI.h"

#include <array>
#include <cstdint>
#include <memory>

/**
 * @class GraphicalBoardDummy
 * Dummy class used as a substitute for GraphicalBoardI classes for testing
 * purposes.
 */
class GraphicalBoardDummy : public GraphicalBoardI {
private:
    std::shared_ptr<NcPlaneWrapperI> _primaryPlane;
    std::array<std::unique_ptr<GraphicalAreaI>, CELL_COUNT> _children;

    void init_child_planes();

    GraphicalBoardDummy(std::shared_ptr<NcPlaneWrapperI> plane);

public:
    /**
     * Constructor for GraphicalBoard dummy.
     *
     * @param plane The primary plane used by the methods of the class.
     *
     * This is needed to create child planes.
     *
     * @see init_child_planes()
     */
    GraphicalBoardDummy(NcPlaneWrapperI *plane);

    void draw_board(const std::array<const char *, SYMBOL_COUNT> SYMBOLS,
                    const uint64_t CELL_CHANNELS) override final;
    void draw_x(const int INDEX) override final;
    void draw_o(const int INDEX) override final;
    std::array<GraphicalAreaI *, CELL_COUNT> get_children() override final;

    void dim_yx(int &ROWS, int &COLS) const override final;
    int get_rows() const override final;
    int get_cols() const override final;

    GraphicalAreaI *create_child(const ncplane_options *nopts) override final;

    int load_nccell(nccell *const c, const char *gcluster) override final;
    int set_base_cell(const nccell *const c) override final;

    int cursor_move_yx(const int X, const int Y) override final;
    int hline(const nccell *const c, const unsigned LEN) override final;
    int vline(const nccell *const c, const unsigned LEN) override final;
    int putc_yx(const int Y, const int X, const nccell *const c) override final;
    void erase() override final;
};

#endif
