#ifndef ALPHA_RING_HALO3ODST_H
#define ALPHA_RING_HALO3ODST_H


#include "offset_halo3odst.h"

#include "module/entry.h"


extern EntrySet g_pHalo3ODSTEntrySet;
inline EntrySet* Halo3ODSTEntrySet() {return &g_pHalo3ODSTEntrySet;};

#define Halo3ODSTEntry(name, offset, returnType, pDetour, ...) \
    returnType pDetour(__VA_ARGS__); \
    typedef returnType (*pDetour##_t)(...); \
    ::Entry name(Halo3ODSTEntrySet(), offset, pDetour); \
    returnType pDetour(__VA_ARGS__)

#endif //ALPHA_RING_HALO3ODST_H
