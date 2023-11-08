#ifndef LEAFBOARD
#define LEAFBOARD

#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/Board.h"

#include <array>
#include <memory>
#include <notcurses/notcurses.h>

class LeafBoard : virtual public Board {
private:
    /**
     * The unicode characters used when drawing the graphical representation of
     * the board.
     *
     * Shared between all instances.
     */
    static std::array<const char *, 3> _symbols;

    /**
     * Array storing ownership of its component cells.
     */
    std::array<LLCell, 9> _cells;

    /**
     * Variable storing the winner of the instance.
     *
     * @see get_winner()
     * @see set_cell_owner()
     * @see Board::check_win()
     */
    CellOwner _winner;

public:
    /**
     * The constructor for LeafBoard.
     *
     * @param ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param PLANE The plane used as the primary plane of the board's new
     * GraphicalBoard.
     *
     * @see Board::Board(std::shared_ptr<NcHandler>, ncplane *const, const
     * uint64_t, std::array<const char *, 3>)
     * @see NcHandler::combine_channels()
     */
    LeafBoard(std::shared_ptr<NcHandler> ncHandler, ncplane *const PLANE);

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
    bool set_cell_owner(const int INDEX, const CellOwner OWNER);

    /**
     * Gets the winner of the entire board.
     *
     * @see _winner
     */
    CellOwner get_winner() const;

    /**
     * Marks primary plane and all child planes of component GraphicalBoard as
     * owned by X.
     *
     * Used when the leaf board is won.
     *
     * @see Board::mGBoard
     */
    void fill_x();

    /**
     * Marks primary plane and all child planes of component GraphicalBoard as
     * owned by O.
     *
     * Used when the leaf board is won.
     *
     * @see Board::mGBoard
     */
    void fill_o();
};

#endif // !LEAFBOARD
