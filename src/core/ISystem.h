#ifndef ALPHA_RING_ISYSTEM_H
#define ALPHA_RING_ISYSTEM_H

#include "Log.h"

class ISystem {
public:
    enum eStatus : bool {
        SYS_OK,
        SYS_ERROR,
    };

    virtual eStatus initialize() = 0;
    virtual eStatus shutdown() = 0;
};

#endif //ALPHA_RING_ISYSTEM_H
