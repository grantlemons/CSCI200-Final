#ifndef NCPLANE_WRAPPERI
#define NCPLANE_WRAPPERI

#include "lib/interfaces/GraphicalAreaI.h"

/**
 * @class NcPlaneWrapperI
 * Interface for NcPlaneWrapper.
 *
 * @see NcPlaneWrapper
 * @see NcPlaneWrapperDummy
 */
class NcPlaneWrapperI : virtual public GraphicalAreaI {
public:
    virtual ~NcPlaneWrapperI() = default;
};

#endif
