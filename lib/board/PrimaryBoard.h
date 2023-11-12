#ifndef PRIMARYBOARD
#define PRIMARYBOARD

#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/Board.h"
#include "lib/board/LeafBoard.h"

#include <array>
#include <memory>
#include <optional>

/**
 * @class PrimaryBoard
 * A representation of the primary/main board for the Tic-Tac-Toe game.
 *
 * Used to represent the logical state of the board.
 * Constituant cells are LeafBoards.
 *
 * @see LeafBoard
 * @see Board
 */
class PrimaryBoard : virtual public Board {
private:
    /**
     * The unicode characters used when drawing the graphical representation of
     * the board.
     *
     * Shared between all instances.
     */
    static std::array<const char *, SYMBOL_COUNT> _symbols;

    /**
     * Array storing ownership of its component LeafBoards.
     */
    std::array<std::unique_ptr<LeafBoard>, CELL_COUNT> _cells;

    /**
     * Helper function to abstract out of the two different constructors.
     *
     * Creates LeafBoards for each cell and places them in the _cells array.
     *
     * @see _cells
     */
    void init_cells();

public:
    /**
     * A constructor for PrimaryBoard using dependency injection.
     *
     * @param ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param gBoard The graphical board object of the parent Board class.
     *
     * @see NcHandler::combine_channels()
     */
    PrimaryBoard(std::shared_ptr<NcHandlerI> ncHandler,
                 std::unique_ptr<GraphicalBoardI> gBoard);

    /**
     * The constructor for PrimaryBoard.
     *
     * Creates constituant LeafBoards to fill _cells.
     *
     * @param ncHandler The handler object used to access the underlying
     * notcurses instance.
     *
     * @see _cells
     * @see def_primary_nopts()
     */
    PrimaryBoard(std::shared_ptr<NcHandlerI> ncHandler);

    ~PrimaryBoard() = default;
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
    std::optional<LeafBoard *> select_board(const unsigned int INDEX);

    CellOwner get_cell_owner(const unsigned int INDEX) const override final;

    void draw() override final;
    void mark_cell(const unsigned int INDEX,
                   const CellOwner OWNER) override final;
};

// Helper functions

/**
 * Returns the options for the plane used in the constituant GraphicalBoard.
 *
 * @todo Replace with something more dynamic.
 * @todo Allow for resizes.
 *
 * @param ncHandler A shared pointer to the handler object used to access the
 * underlying notcurses instance.
 * @return An ncplane_options struct describing the configuration options.
 */
ncplane_options def_primary_nopts(std::shared_ptr<NcHandlerI> ncHandler);

#endif // !PRIMARYBOARD
