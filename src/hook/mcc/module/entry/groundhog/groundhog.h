#pragma once

#include "game/groundhog/native_groundhog.h"
#include "offset_groundhog.h"

#include "../entry.h"

extern EntrySet g_pGroundHogEntrySet;
inline EntrySet* GroundHogEntrySet() {return &g_pGroundHogEntrySet;};

#define GroundHogEntry(name, offset, returnType, pDetour, ...) \
    returnType pDetour(__VA_ARGS__); \
    typedef returnType (*pDetour##_t)(...); \
    ::Entry name(GroundHogEntrySet(), offset, pDetour); \
    returnType pDetour(__VA_ARGS__)

