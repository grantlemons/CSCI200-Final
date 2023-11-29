#ifndef LEAFBOARD
#define LEAFBOARD

#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/ABoard.h"
#include "lib/interfaces/IGraphicalArea.h"
#include "lib/interfaces/IGraphicalBoard.h"
#include "lib/interfaces/INcPlaneWrapper.h"

#include <array>

/**
 * @class LeafBoard
 * A representation of the subboards/leaf boards of the primary board in the
 * Tic-Tac-Toe game.
 *
 * i.e. Each instance of class LeafBoard represents one of the cells of the
 * PrimaryBoard
 *
 * Used to represent the logical state of the board.
 * Constituant cells are of the type LLCell (a typedef).
 */
class LeafBoard : virtual public ABoard {
private:
    /**
     * The unicode characters used when drawing the graphical representation of
     * the board.
     *
     * Shared between all instances.
     */
    static const std::array<const char *, SYMBOL_COUNT> _SYMBOLS;

    /**
     * Component graphical board used to represent actions on the logical board
     * graphically.
     */
    IGraphicalBoard *_pGBoard;

    /**
     * Array storing ownership of its component cells.
     */
    std::array<LLCell, CELL_COUNT> _cells;

    /**
     * Variable storing the winner of the instance.
     */
    CELL_OWNER _winner;

public:
    /**
     * A constructor for LeafBoard using dependency injection.
     *
     * @param P_ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param P_gBoard The graphical board object of the parent Board class.
     */
    LeafBoard(INcHandler *const P_ncHandler, IGraphicalBoard *const P_gBoard);

    ~LeafBoard() override = default;
    LeafBoard(LeafBoard &) = delete;
    void operator=(const LeafBoard &) = delete;

    [[nodiscard]] IGraphicalBoard *getGraphicalBoard() const override final;

    [[nodiscard]] CELL_OWNER
    get_cell_owner(const int INDEX) const override final;

    /**
     * Attempts to set the owner of the given index.
     *
     * If setting the owner of this cell wins the LeafBoard instance as a whole,
     * sets _winner variable.
     *
     * @param INDEX The index of the cell to set the owner of.
     * @param OWNER The player to set the owner of the cell to.
     */
    void set_cell_owner(const int INDEX, const CELL_OWNER OWNER);

    /**
     * Gets the winner of the entire board.
     */
    [[nodiscard]] CELL_OWNER get_winner() const;

    void draw() override final;
};

#endif // !LEAFBOARD
