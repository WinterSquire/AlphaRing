#ifndef ALPHA_RING_HALO1_H
#define ALPHA_RING_HALO1_H

#include "game/halo1/native_halo1.h"
#include "offset_halo1.h"

#include "../entry.h"


extern EntrySet g_pHalo1EntrySet;
inline EntrySet* Halo1EntrySet() {return &g_pHalo1EntrySet;};

#define Halo1Entry(name, offset, returnType, pDetour, ...) \
    returnType pDetour(__VA_ARGS__); \
    typedef returnType (*pDetour##_t)(...); \
    ::Entry name(Halo1EntrySet(), offset, pDetour); \
    returnType pDetour(__VA_ARGS__)


#endif //ALPHA_RING_HALO1_H
