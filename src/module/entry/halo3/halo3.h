#ifndef ALPHA_RING_MODULE_ENTRY_HALO3_H
#define ALPHA_RING_MODULE_ENTRY_HALO3_H

#include "offset_halo3.h"

#include "../entry.h"


extern EntrySet g_pHalo3EntrySet;
inline EntrySet* Halo3EntrySet() {return &g_pHalo3EntrySet;};

#define Halo3Entry(name, offset, pDetour) ::Entry name(Halo3EntrySet(), offset, pDetour)

#endif //ALPHA_RING_MODULE_ENTRY_HALO3_H
