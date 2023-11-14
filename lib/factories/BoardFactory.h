#ifndef BOARD_FACTORY
#define BOARD_FACTORY

#include "lib/board/LeafBoard.h"
#include "lib/board/PrimaryBoard.h"
#include "lib/factories/AbstractBoardFactory.h"
#include "lib/interfaces/IGraphicalArea.h"
#include "lib/interfaces/INcHandler.h"
#include "lib/interfaces/INcPlaneWrapper.h"

#include <memory>

/**
 * @class BoardFactory
 * Factory pattern for initializing boards.
 */
class BoardFactory : virtual public AbstractBoardFactory {
private:
    std::unique_ptr<INcHandler> _ncHandler;
    PrimaryBoard _primaryBoard;

public:
    /**
     * Default constructor for factory.
     */
    BoardFactory();

    INcHandler *getNcHandler() override final;
    PrimaryBoard *getPrimaryBoard() override final;
    IGraphicalArea *getPrimaryGraphicalBoard() override final;
    LeafBoard *getLeafBoard(const int INDEX) override final;
    IGraphicalArea *getLeafGraphicalBoard(const int INDEX) override final;
};

#endif // !BOARD_FACTORY
