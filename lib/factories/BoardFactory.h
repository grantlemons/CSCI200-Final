#ifndef BOARD_FACTORY
#define BOARD_FACTORY

#include "lib/board/LeafBoard.h"
#include "lib/board/PrimaryBoard.h"
#include "lib/factories/AbstractBoardFactory.h"
#include "lib/interfaces/GraphicalAreaI.h"
#include "lib/interfaces/NcHandlerI.h"
#include "lib/interfaces/NcPlaneWrapperI.h"

#include <memory>

/**
 * @class BoardFactory
 * Factory pattern for initializing boards.
 */
class BoardFactory : virtual public AbstractBoardFactory {
private:
    std::unique_ptr<NcHandlerI> _ncHandler;
    PrimaryBoard _primaryBoard;

public:
    /**
     * Default constructor for factory.
     */
    BoardFactory();

    NcHandlerI *getNcHandler() override final;
    PrimaryBoard *getPrimaryBoard() override final;
    GraphicalAreaI *getPrimaryGraphicalBoard() override final;
    LeafBoard *getLeafBoard(const int INDEX) override final;
    GraphicalAreaI *getLeafGraphicalBoard(const int INDEX) override final;
};

#endif // !BOARD_FACTORY
