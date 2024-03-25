#ifndef ALPHA_RING_NATIVE_H
#define ALPHA_RING_NATIVE_H

#include "../../../os/ThreadLocalStorage.h"

namespace Native {
    bool Init(__int64 hModule);
    const ThreadLocalStorage& getTLS();
    void Shutdown();
};


#endif //ALPHA_RING_NATIVE_H
