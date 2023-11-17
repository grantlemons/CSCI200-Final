#ifndef PRIMARYBOARD
#define PRIMARYBOARD

#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/ABoard.h"
#include "lib/board/LeafBoard.h"
#include "lib/graphical_board/PrimaryGraphicalBoard.h"
#include "lib/interfaces/IGraphicalArea.h"
#include "lib/interfaces/IGraphicalBoard.h"

#include <array>
#include <memory>
#include <notcurses/notcurses.h>
#include <optional>

/**
 * @class PrimaryBoard
 * A representation of the primary/main board for the Tic-Tac-Toe game.
 *
 * Used to represent the logical state of the board.
 * Constituant cells are LeafBoards.
 */
class PrimaryBoard : virtual public ABoard {
private:
    /**
     * The unicode characters used when drawing the graphical representation of
     * the board.
     *
     * Shared between all instances.
     */
    const static std::array<const char *, SYMBOL_COUNT> _symbols;

    /**
     * Component graphical board used to represent actions on the logical board
     * graphically.
     */
    std::unique_ptr<IGraphicalBoard> _gBoard;

    /**
     * Array storing ownership of its component LeafBoards.
     */
    std::array<std::unique_ptr<LeafBoard>, CELL_COUNT> _cells;

    /**
     * Helper function to abstract out of the two different constructors.
     *
     * Creates LeafBoards for each cell and places them in the _cells array.
     */
    void init_cells();

public:
    /**
     * A constructor for PrimaryBoard using dependency injection.
     *
     * @param ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param gBoard The graphical board object of the parent Board class.
     */
    PrimaryBoard(INcHandler *const P_ncHandler,
                 std::unique_ptr<IGraphicalBoard> gBoard);

    /**
     * The constructor for PrimaryBoard.
     *
     * Creates constituant LeafBoards to fill _cells.
     *
     * @param ncHandler The handler object used to access the underlying
     * notcurses instance.
     */
    PrimaryBoard(INcHandler *const P_ncHandler);

    ~PrimaryBoard() override = default;
    PrimaryBoard(PrimaryBoard &) = delete;
    void operator=(const PrimaryBoard &) = delete;

    /**
     * Gets a pointer to one of the constituant LeafBoards.
     *
     * Used when selecting which LeafBoard to play on.
     *
     * @param INDEX The index of the desired LeafBoard.
     * @return An optional pointer to the constituant LeafBoard.
     *
     * If the selected LeafBoard is already owned, the function returns nullopt.
     */
    std::optional<LeafBoard *> select_board(const int INDEX);

    /**
     * Getter for a cell of the PrimaryBoard.
     *
     * @param INDEX The index of the cell within the PrimaryBoard.
     */
    [[nodiscard]] LeafBoard *getLeafBoard(const int INDEX) const;
    [[nodiscard]] IGraphicalBoard *getGraphicalBoard() const override final;

    [[nodiscard]] CellOwner
    get_cell_owner(const int INDEX) const override final;

    void draw() override final;

    /**
     * Returns the options for the plane used in the constituant GraphicalBoard.
     *
     * @todo Replace with something more dynamic.
     * @todo Allow for resizes.
     *
     * @param ncHandler A shared pointer to the handler object used to access
     * the underlying notcurses instance.
     * @return An ncplane_options struct describing the configuration options.
     */
    static ncplane_options defPrimaryNopts(INcHandler *const P_ncHandler);
};

#endif // !PRIMARYBOARD
