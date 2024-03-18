#ifndef ALPHA_RING_NATIVE_H
#define ALPHA_RING_NATIVE_H

#include "Common.h"

namespace Native {
    bool updateData(Module&& data);
    const Module& getModuleData();

    __int64 GetModuleHandle();
};


#endif //ALPHA_RING_NATIVE_H
