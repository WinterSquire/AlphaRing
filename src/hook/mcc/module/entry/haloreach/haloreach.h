#pragma once

#include "game/haloreach/native_haloreach.h"
#include "offset_haloreach.h"

#include "../entry.h"


extern EntrySet g_pHaloReachEntrySet;
inline EntrySet* HaloReachEntrySet() {return &g_pHaloReachEntrySet;};

#define HaloReachEntry(name, offset, returnType, pDetour, ...) \
    returnType pDetour(__VA_ARGS__); \
    typedef returnType (*pDetour##_t)(...); \
    ::Entry name(HaloReachEntrySet(), offset, pDetour); \
    returnType pDetour(__VA_ARGS__)
