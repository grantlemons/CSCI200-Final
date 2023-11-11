#ifndef BOARD
#define BOARD

#include "lib/GraphicalBoard.h"
#include "lib/NcHandler.h"
#include "lib/Shared.h"

#include <array>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>

/**
 * @class Board
 * Abstract class representation of a logical board.
 */
class Board {
private:
    /** The handler object used to access the underlying
     * notcurses instance.
     */
    std::shared_ptr<NcHandler> _ncHandler;

    /**
     * Component graphical board used to represent actions on the logical board
     * graphically.
     */
    std::unique_ptr<GraphicalBoard> _GBoard;

protected:
    /**
     * A constructor that uses dependency injection.
     *
     * @param ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param GBoard The associated graphical board to construct with.
     */
    Board(std::shared_ptr<NcHandler> ncHandler,
          std::unique_ptr<GraphicalBoard> GBoard);

    /**
     * A constructor that takes a plane to use for the underlying graphical
     * board.
     *
     * @param ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param PLANE The plane used as the primary plane of the new
     * _GBoard.
     */
    Board(std::shared_ptr<NcHandler> ncHandler, ncplane *const PLANE);

    /**
     * A constructor that takes raw info for the underlying graphical board.
     *
     * @param ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param NOPTS The configuration used to form the primary plane.
     *
     * @see ncplane_create()
     */
    Board(std::shared_ptr<NcHandler> ncHandler, const ncplane_options NOPTS);

    /**
     * Getter for the associated GraphicalBoard instance.
     *
     * @return A pointer to the private GraphicalBoard.
     */
    GraphicalBoard *getGraphicalBoard() const;

    /**
     * Getter for the associated NcHandler instance.
     *
     * @return A pointer to the private NcHandler.
     */
    std::shared_ptr<NcHandler> getNcHandler() const;

    virtual ~Board() = default;

public:
    Board(Board &) = delete;
    void operator=(const Board &) = delete;

    /**
     * Checks if the given player has won the current board.
     *
     * Can be called after any move with the player that just moved.
     * Since a player can only win after making a move, checking a single player
     * is optimal.
     *
     * @param INDEX The index of a cell known to be owned by the given player.
     * @param OWNER The player to check the victory of.
     * @return If the given player won or not.
     *
     * @see get_cell_owner()
     */
    virtual bool check_win(const unsigned int INDEX,
                           const CellOwner OWNER) const;

    /**
     * Gets the owner of a given index.
     *
     * @param INDEX the index of the cell to check ownership.
     * @return The owner of the cell (Can be NONE variant).
     */
    virtual CellOwner get_cell_owner(const unsigned int INDEX) const = 0;

    /**
     * Uses the component GraphicalBoard to draw a Tic-Tac-Toe board.
     *
     * @see _GBoard
     * @see GraphicalBoard::draw_board()
     */
    virtual void draw() = 0;

    /**
     * Uses the component GraphicalBoard to mark the owner of a cell as X.
     *
     * @see _GBoard
     * @see GraphicalBoard::draw_x()
     */
    virtual void draw_x(const unsigned int INDEX);

    /**
     * Uses the component GraphicalBoard to mark the owner of a cell as O.
     *
     * @see _GBoard
     * @see GraphicalBoard::draw_o()
     */
    virtual void draw_o(const unsigned int INDEX);

    /**
     * Defines the way Board types are outputted to streams.
     */
    friend std::ostream &operator<<(std::ostream &out, const Board &BRD);
};

// Helper functions

/**
 * Mod function that takes into account negative numbers.
 *
 * @code{.cpp}
 * negative_mod(-1, 10) == 9
 * @endcode
 *
 * @code{.cpp}
 * negative_mod(1, 10) == 1
 * @endcode
 *
 * @param A The dividend of the modulus operation.
 * @param B The divisor of the modulus operation.
 * @return The result of the modulus operation.
 *
 * @relates Board
 */
constexpr unsigned int negative_mod(const int A, const int B);

/**
 * Gets the other indicies on a certain row of a 3x3 grid.
 *
 * Indicies are arranged like so:
 * 0|1|2
 * 3|4|5
 * 6|7|8
 *
 * @param [in] INDEX The known index on a row.
 * @param [out] other1 The first other index in the same row.
 * @param [out] other2 The second other index in the same row.
 *
 * @see vertical_others()
 *
 * @relates Board
 */
constexpr void horizontal_others(const unsigned int INDEX, unsigned int &other1,
                                 unsigned int &other2);

/**
 * Gets the other indicies on a certain column of a 3x3 grid.
 *
 * Indicies are arranged like so:
 * 0|1|2
 * 3|4|5
 * 6|7|8
 *
 * @param [in] INDEX The known index on a column.
 * @param [out] other1 The first other index in the same column.
 * @param [out] other2 The second other index in the same column.
 *
 * @see horizontal_others()
 *
 * @relates Board
 */
constexpr void vertical_others(const unsigned int INDEX, unsigned int &other1,
                               unsigned int &other2);

/**
 * Gets the other indicies of a diagonal line on a 3x3 grid.
 *
 * Indicies are arranged like so:
 * 0|1|2
 * 3|4|5
 * 6|7|8
 *
 * This function is only used for the diagonal from index 0 to 8.
 *
 * @param [in] INDEX The known index in the diagonal. Must be a multiple of 4.
 * @param [out] other1 The first other index in the diagonal.
 * @param [out] other2 The second other index in the diagonal.
 *
 * @see diagonal_twos_others()
 *
 * @relates Board
 */
constexpr void diagonal_fours_others(const unsigned int INDEX,
                                     unsigned int &other1,
                                     unsigned int &other2);

/**
 * Gets the other indicies of a diagonal line on a 3x3 grid.
 *
 * Indicies are arranged like so:
 * 0|1|2
 * 3|4|5
 * 6|7|8
 *
 * This function is only used for the diagonal from index 2 to 6.
 *
 * @param [in] INDEX The known index in the diagonal. Must be a multiple of 2
 * (that is not a multiple of 4 with the exception of 4 itself).
 * @param [out] other1 The first other index in the diagonal.
 * @param [out] other2 The second other index in the diagonal.
 *
 * @see diagonal_twos_others()
 *
 * @relates Board
 */
constexpr void diagonal_twos_others(const unsigned int INDEX,
                                    unsigned int &other1, unsigned int &other2);

#endif // !BOARD
