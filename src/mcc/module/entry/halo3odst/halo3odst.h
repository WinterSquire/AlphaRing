#pragma once

#include <halo3odst.h>

#include "mcc/module/entry/entry.h"

extern EntrySet g_pHalo3ODSTEntrySet;
inline EntrySet* Halo3ODSTEntrySet() {return &g_pHalo3ODSTEntrySet;};

#define Halo3ODSTEntry(name, offset, returnType, pDetour, ...) \
    returnType pDetour(__VA_ARGS__); \
    typedef returnType (*pDetour##_t)(...); \
    ::Entry name(Halo3ODSTEntrySet(), offset, pDetour); \
    returnType pDetour(__VA_ARGS__)
