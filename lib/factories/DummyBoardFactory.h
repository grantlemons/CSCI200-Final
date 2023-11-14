#ifndef DUMMY_BOARD_FACTORY
#define DUMMY_BOARD_FACTORY

#include "lib/board/LeafBoard.h"
#include "lib/board/PrimaryBoard.h"
#include "lib/factories/AbstractBoardFactory.h"
#include "lib/interfaces/GraphicalAreaI.h"
#include "lib/interfaces/NcHandlerI.h"
#include "lib/interfaces/NcPlaneWrapperI.h"

#include <memory>

/**
 * @class DummyBoardFactory
 * Factory pattern for initializing Dummy Boards.
 */
class DummyBoardFactory : virtual public AbstractBoardFactory {
private:
    std::unique_ptr<NcHandlerI> _ncHandler;
    NcPlaneWrapperI *_primaryPlane;
    std::unique_ptr<GraphicalBoardI> _graphicalBoard;
    PrimaryBoard _primaryBoard;

public:
    /**
     * Default constructor for factory.
     */
    DummyBoardFactory();

    NcHandlerI *getNcHandler() override final;
    PrimaryBoard *getPrimaryBoard() override final;
    GraphicalAreaI *getPrimaryGraphicalBoard() override final;
    LeafBoard *getLeafBoard(const int INDEX) override final;
    GraphicalAreaI *getLeafGraphicalBoard(const int INDEX) override final;
};

#endif // !DUMMY_BOARD_FACTORY
