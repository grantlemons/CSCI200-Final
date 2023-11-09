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
    static std::array<const char *, 3> _symbols;

    /**
     * Array storing ownership of its component LeafBoards.
     */
    std::array<LeafBoard *, 9> _cells;

public:
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
     * @see Board(std::shared_ptr<NcHandler>, const ncplane_options, const
     * uint64_t, std::array<const char *, 3>)
     */
    PrimaryBoard(std::shared_ptr<NcHandler> ncHandler);

    ~PrimaryBoard();
    PrimaryBoard(PrimaryBoard &) = delete;
    void operator=(const PrimaryBoard &) = delete;

    CellOwner get_cell_owner(const unsigned int INDEX) const override final;

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

    void draw_x(const unsigned int INDEX) override final;
    void draw_o(const unsigned int INDEX) override final;
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
ncplane_options def_primary_nopts(std::shared_ptr<NcHandler> ncHandler);

#endif // !PRIMARYBOARD
