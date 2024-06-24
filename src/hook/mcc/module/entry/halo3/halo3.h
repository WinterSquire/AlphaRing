#pragma once

#include "game/halo3/native_halo3.h"
#include "offset_halo3.h"

#include "../entry.h"

extern EntrySet g_pHalo3EntrySet;
inline EntrySet* Halo3EntrySet() {return &g_pHalo3EntrySet;};

#define Halo3Entry(name, offset, returnType, pDetour, ...) \
    returnType pDetour(__VA_ARGS__);  \
    typedef returnType (*pDetour##_t)(__VA_ARGS__); \
    ::Entry name(Halo3EntrySet(), offset, pDetour); \
    returnType pDetour(__VA_ARGS__)
