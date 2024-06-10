#ifndef ALPHA_RING_HALOREACH_H
#define ALPHA_RING_HALOREACH_H


#include "offset_haloreach.h"

#include "module/entry.h"


extern EntrySet g_pHaloReachEntrySet;
inline EntrySet* HaloReachEntrySet() {return &g_pHaloReachEntrySet;};

#define HaloReachEntry(name, offset, returnType, pDetour, ...) \
    returnType pDetour(__VA_ARGS__); \
    typedef returnType (*pDetour##_t)(...); \
    ::Entry name(HaloReachEntrySet(), offset, pDetour); \
    returnType pDetour(__VA_ARGS__)


#endif //ALPHA_RING_HALOREACH_H
