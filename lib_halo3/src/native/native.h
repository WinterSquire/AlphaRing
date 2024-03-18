#ifndef ALPHA_RING_NATIVE_H
#define ALPHA_RING_NATIVE_H

#include "Common.h"

namespace Native {
    bool sethModule(__int64 hModule);
    __int64 gethModule();

    bool setModule(Module && module);
    const Module& getModule();

    bool setTEB(__int64 teb);
    __int64 getTEB();
};


#endif //ALPHA_RING_NATIVE_H
