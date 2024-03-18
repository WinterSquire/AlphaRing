#ifndef ALPHA_RING_OBJECTINFO_H
#define ALPHA_RING_OBJECTINFO_H

#include "objects.h"

struct ObjectInfo {
    __int64 v0;
    __int64 v1;
    Objects_t* address;

    inline bool isValid();
};


#endif //ALPHA_RING_OBJECTINFO_H
