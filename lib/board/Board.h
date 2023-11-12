#ifndef BOARD
#define BOARD

#include "gsl/assert"
#include "gsl/narrow"
#include "lib/GraphicalBoard.h"
#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/interfaces/NcPlaneWrapperI.h"

#include <array>
#include <cmath>
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
    std::shared_ptr<NcHandlerI> _ncHandler;

    /**
     * Component graphical board used to represent actions on the logical board
     * graphically.
     */
    std::unique_ptr<GraphicalBoardI> _gBoard;

protected:
    /**
     * A constructor that uses dependency injection.
     *
     * @param ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param gBoard The associated graphical board to construct with.
     */
    Board(std::shared_ptr<NcHandlerI> ncHandler,
          std::unique_ptr<GraphicalBoardI> gBoard);

    /**
     * A constructor that takes a plane to use for the underlying graphical
     * board.
     *
     * @param ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param PLANE The plane used as the primary plane of the new
     * _gBoard.
     */
    Board(std::shared_ptr<NcHandlerI> ncHandler,
          std::unique_ptr<NcPlaneWrapperI> PLANE);

    /**
     * A constructor that takes raw info for the underlying graphical board.
     *
     * @param ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param NOPTS The configuration used to form the primary plane.
     *
     * @see ncplane_create()
     */
    Board(std::shared_ptr<NcHandlerI> ncHandler, const ncplane_options NOPTS);

    /**
     * Getter for the associated GraphicalBoard instance.
     *
     * @return A pointer to the private GraphicalBoard.
     */
    GraphicalBoardI *getGraphicalBoard() const;

    /**
     * Getter for the associated NcHandler instance.
     *
     * @return A pointer to the private NcHandler.
     */
    std::shared_ptr<NcHandlerI> getNcHandler() const;

    virtual ~Board() = default;

    Board(Board &) = delete;
    void operator=(const Board &) = delete;

public:
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
    virtual bool check_win(const int INDEX, const CellOwner OWNER) const;

    /**
     * Gets the owner of a given index.
     *
     * @param INDEX the index of the cell to check ownership.
     * @return The owner of the cell (Can be NONE variant).
     */
    virtual CellOwner get_cell_owner(const int INDEX) const = 0;

    /**
     * Uses the component GraphicalBoard to draw a Tic-Tac-Toe board.
     *
     * @see _gBoard
     * @see GraphicalBoard::draw_board()
     */
    virtual void draw() = 0;

    /**
     * Uses the component GraphicalBoard to mark the owner of a cell
     * appropriately.
     *
     * @param INDEX The index of the cell to mark.
     * @param OWNER The user for whom to mark the cell.
     *
     * @see _gBoard
     * @see GraphicalBoard::draw_x()
     * @see GraphicalBoard::draw_o()
     */
    virtual void mark_cell(const int INDEX, const CellOwner OWNER);

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
inline constexpr int negative_mod(const int A, const int B) {
    return A - (B * gsl::narrow<int>(std::floor(gsl::narrow<double>(A) / B)));
}

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
inline constexpr void horizontal_others(const int INDEX, int &other1,
                                        int &other2) {
    Expects(INDEX >= 0 && INDEX <= 9);

    const int ROW_LEN = 3;
    other1 = negative_mod(INDEX - 1, ROW_LEN) + ROW_LEN;
    other2 = negative_mod(INDEX + 1, ROW_LEN) + ROW_LEN;

    Expects(other1 != other2);
    Expects(other1 != INDEX && other2 != INDEX);
    Expects(other1 >= 0 && other1 <= 9);
    Expects(other2 >= 0 && other2 <= 9);
}

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
inline constexpr void vertical_others(const int INDEX, int &other1,
                                      int &other2) {
    Expects(INDEX >= 0 && INDEX <= 9);

    const int ROW_LEN = 3;
    other1 = negative_mod(INDEX - ROW_LEN, CELL_COUNT);
    other2 = negative_mod(INDEX + ROW_LEN, CELL_COUNT);

    Expects(other1 != other2);
    Expects(other1 != INDEX && other2 != INDEX);
    Expects(other1 >= 0 && other1 <= 9);
    Expects(other2 >= 0 && other2 <= 9);
}

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
inline constexpr void diagonal_fours_others(const int INDEX, int &other1,
                                            int &other2) {
    Expects(INDEX == 0 || INDEX == 4 || INDEX == 8);

    other1 = negative_mod(INDEX - 4, CELL_COUNT + 3);
    other2 = negative_mod(INDEX + 4, CELL_COUNT + 3);

    Expects(other1 != other2);
    Expects(other1 != INDEX && other2 != INDEX);
    Expects(other1 == 0 || other1 == 4 || other1 == 8);
    Expects(other2 == 0 || other2 == 4 || other2 == 8);
}

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
inline constexpr void diagonal_twos_others(const int INDEX, int &other1,
                                           int &other2) {
    Expects(INDEX == 2 || INDEX == 4 || INDEX == 6);

    other1 = negative_mod(INDEX, 6) + 2;
    other2 = negative_mod(INDEX + 2, 6) + 2;

    Expects(other1 != other2);
    Expects(other1 != INDEX && other2 != INDEX);
    Expects(other1 == 2 || other1 == 4 || other1 == 6);
    Expects(other2 == 2 || other2 == 4 || other2 == 6);
}

#endif // !BOARD
