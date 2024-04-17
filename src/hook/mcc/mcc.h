#ifndef ALPHA_RING_MCC_H
#define ALPHA_RING_MCC_H

#include "module.h"

namespace MCCHook {
    using Callback_t = void(*)(void*);

    bool Initialize(Callback_t load_callback, Callback_t unload_callback);
    void Shutdown();
}

#endif //ALPHA_RING_MCC_H
