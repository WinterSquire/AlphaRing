#ifndef ALPHA_RING_INTERFACE_H
#define ALPHA_RING_INTERFACE_H

#include "../core/ISystem.h"

extern ISystem* g_pInterface;

inline ISystem* Interface() {return g_pInterface;}

#endif //ALPHA_RING_INTERFACE_H
