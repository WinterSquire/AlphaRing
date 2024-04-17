#ifndef ALPHA_RING_HALO3_H
#define ALPHA_RING_HALO3_H

#include "./entry/engine/engine.h"
#include "./entry/world/world.h"

namespace Halo3Hook {
    bool Init();
    bool Update(__int64 hModule);
    void Shutdown();
};


#endif //ALPHA_RING_HALO3_H
