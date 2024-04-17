#ifndef ALPHA_RING_EXTERNALCONSOLE_H
#define ALPHA_RING_EXTERNALCONSOLE_H

#include "ISystem.h"

extern ISystem* g_pExternalConsole;
inline ISystem* ExternalConsole() {return g_pExternalConsole;}

#endif //ALPHA_RING_EXTERNALCONSOLE_H
