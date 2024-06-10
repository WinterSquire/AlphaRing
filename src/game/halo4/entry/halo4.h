#ifndef ALPHA_RING_HALO4_H
#define ALPHA_RING_HALO4_H


#include "offset_halo4.h"

#include "module/entry.h"


extern EntrySet g_pHalo4EntrySet;
inline EntrySet* Halo4EntrySet() {return &g_pHalo4EntrySet;};

#define Halo4Entry(name, offset, returnType, pDetour, ...) \
    returnType pDetour(__VA_ARGS__); \
    typedef returnType (*pDetour##_t)(...); \
    ::Entry name(Halo4EntrySet(), offset, pDetour); \
    returnType pDetour(__VA_ARGS__)


#endif //ALPHA_RING_HALO4_H
