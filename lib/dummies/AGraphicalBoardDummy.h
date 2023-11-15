#ifndef G_BOARD_DUMMY
#define G_BOARD_DUMMY

#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/interfaces/IGraphicalArea.h"
#include "lib/interfaces/IGraphicalBoard.h"
#include "lib/interfaces/INcPlaneWrapper.h"

#include <array>
#include <memory>

/**
 * @class AGraphicalBoardDummy
 * Abstract class for dummies used as a substitute for GraphicalBoardI classes
 * for testing purposes.
 */
class AGraphicalBoardDummy : virtual public IGraphicalBoard {
private:
    std::shared_ptr<INcPlaneWrapper> _primaryPlane;
    std::array<std::unique_ptr<IGraphicalArea>, CELL_COUNT> _children;

protected:
    std::shared_ptr<INcPlaneWrapper> get_primary_plane();
    void set_children(std::array<std::unique_ptr<IGraphicalArea>, CELL_COUNT>);

public:
    virtual std::array<std::unique_ptr<IGraphicalArea>, CELL_COUNT>
    create_children() = 0;

    AGraphicalBoardDummy(std::shared_ptr<INcPlaneWrapper> plane);

    ~AGraphicalBoardDummy() override = default;

    void draw_board(const std::array<const char *, SYMBOL_COUNT> SYMBOLS,
                    const uint64_t CELL_CHANNELS) override final;
    void draw_x(const int INDEX) override final;
    void draw_o(const int INDEX) override final;
    std::array<IGraphicalArea *, CELL_COUNT> get_children() override final;

    void dim_yx(int &ROWS, int &COLS) const override final;
    [[nodiscard]] int get_rows() const override final;
    [[nodiscard]] int get_cols() const override final;

    IGraphicalArea *create_child(const ncplane_options *nopts) override final;

    int load_nccell(nccell *const P_c, const char *gcluster) override final;
    int set_base_cell(const nccell *const P_c) override final;

    int cursor_move_yx(const int X, const int Y) override final;
    int hline(const nccell *const P_c, const unsigned LEN) override final;
    int vline(const nccell *const P_c, const unsigned LEN) override final;
    int putc_yx(const int Y, const int X,
                const nccell *const P_c) override final;
    void erase() override final;
};

#endif
