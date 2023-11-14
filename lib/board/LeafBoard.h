#ifndef LEAFBOARD
#define LEAFBOARD

#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/BoardA.h"
#include "lib/interfaces/GraphicalAreaI.h"
#include "lib/interfaces/GraphicalBoardI.h"
#include "lib/interfaces/NcPlaneWrapperI.h"

#include <array>
#include <memory>
#include <notcurses/notcurses.h>

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
 *
 * @see PrimaryBoard
 * @see Board
 */
class LeafBoard : virtual public BoardA {
private:
    /**
     * The unicode characters used when drawing the graphical representation of
     * the board.
     *
     * Shared between all instances.
     */
    static std::array<const char *, SYMBOL_COUNT> _symbols;

    /**
     * Component graphical board used to represent actions on the logical board
     * graphically.
     */
    GraphicalBoardI *_gBoard;

    /**
     * Array storing ownership of its component cells.
     */
    std::array<LLCell, CELL_COUNT> _cells;

    /**
     * Variable storing the winner of the instance.
     *
     * @see get_winner()
     * @see set_cell_owner()
     * @see Board::check_win()
     */
    CellOwner _winner;

    GraphicalBoardI *getGraphicalBoard() const override final;

public:
    /**
     * A constructor for LeafBoard using dependency injection.
     *
     * @param ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param gBoard The graphical board object of the parent Board class.
     *
     * @see NcHandler::combine_channels()
     */
    LeafBoard(std::shared_ptr<NcHandlerI> ncHandler, GraphicalBoardI *gBoard);

    ~LeafBoard() = default;
    LeafBoard(LeafBoard &) = delete;
    void operator=(const LeafBoard &) = delete;

    CellOwner get_cell_owner(const int INDEX) const override final;

    /**
     * Attempts to set the owner of the given index.
     *
     * If setting the owner of this cell wins the LeafBoard instance as a whole,
     * sets _winner variable.
     *
     * @param INDEX The index of the cell to set the owner of.
     * @param OWNER The player to set the owner of the cell to.
     * @return Success or failure.
     *
     * @see _cells
     * @see _winner
     */
    void set_cell_owner(const int INDEX, const CellOwner OWNER);

    /**
     * Gets the winner of the entire board.
     *
     * @see _winner
     */
    CellOwner get_winner() const;

    void draw() override final;

    /**
     * Uses the component GraphicalBoard to mark the owner of the board
     * appropriately.
     *
     * @param OWNER The user for whom to mark the board.
     *
     * @see Board::getGraphicalBoard()
     * @see GraphicalBoard::fill_x()
     * @see GraphicalBoard::fill_o()
     */
    void mark_fill(const CellOwner OWNER);
};

#endif // !LEAFBOARD
