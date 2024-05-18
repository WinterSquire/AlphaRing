#ifndef ALPHA_RING_HALO2_H
#define ALPHA_RING_HALO2_H


#include "offset_halo2.h"

#include "module/entry.h"


extern EntrySet g_pHalo2EntrySet;
inline EntrySet* Halo2EntrySet() {return &g_pHalo2EntrySet;};

#define Halo2Entry(name, offset, returnType, pDetour, ...) \
    returnType pDetour(__VA_ARGS__); \
    typedef returnType (*pDetour##_t)(...); \
    ::Entry name(Halo2EntrySet(), offset, pDetour); \
    returnType pDetour(__VA_ARGS__)


#endif //ALPHA_RING_HALO2_H
