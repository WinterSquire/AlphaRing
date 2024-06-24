#pragma once

#include "game/halo3odst/native_halo3odst.h"
#include "offset_halo3odst.h"

#include "../entry.h"


extern EntrySet g_pHalo3ODSTEntrySet;
inline EntrySet* Halo3ODSTEntrySet() {return &g_pHalo3ODSTEntrySet;};

#define Halo3ODSTEntry(name, offset, returnType, pDetour, ...) \
    returnType pDetour(__VA_ARGS__); \
    typedef returnType (*pDetour##_t)(...); \
    ::Entry name(Halo3ODSTEntrySet(), offset, pDetour); \
    returnType pDetour(__VA_ARGS__)
