#ifndef ALPHA_RING_HOOK_H
#define ALPHA_RING_HOOK_H

#include "core/ISystem.h"

extern ISystem* g_pHook;

inline ISystem* Hook() {return g_pHook;}

#endif //ALPHA_RING_HOOK_H
