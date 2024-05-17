#ifndef ALPHA_RING_HALOREACH_H
#define ALPHA_RING_HALOREACH_H


#include "offset_haloreach.h"

#include "../entry.h"


extern EntrySet g_pHaloReachEntrySet;
inline EntrySet* HaloReachEntrySet() {return &g_pHaloReachEntrySet;};

#define HaloReachEntry(name, offset, pDetour) ::Entry name(HaloReachEntrySet(), offset, pDetour)


#endif //ALPHA_RING_HALOREACH_H
