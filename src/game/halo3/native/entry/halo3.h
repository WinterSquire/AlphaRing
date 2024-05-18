#ifndef ALPHA_RING_MODULE_ENTRY_HALO3_H
#define ALPHA_RING_MODULE_ENTRY_HALO3_H

#include "offset_halo3.h"

#include "module/entry.h"


extern EntrySet g_pHalo3EntrySet;
inline EntrySet* Halo3EntrySet() {return &g_pHalo3EntrySet;};

#define Halo3Entry(name, offset, returnType, pDetour, ...) \
    returnType pDetour(__VA_ARGS__);  \
    typedef returnType (*pDetour##_t)(__VA_ARGS__); \
    ::Entry name(Halo3EntrySet(), offset, pDetour); \
    returnType pDetour(__VA_ARGS__)

#endif //ALPHA_RING_MODULE_ENTRY_HALO3_H
