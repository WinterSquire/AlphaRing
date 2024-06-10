#ifndef ALPHA_RING_GROUNDHOG_H
#define ALPHA_RING_GROUNDHOG_H


#include "offset_groundhog.h"

#include "module/entry.h"


extern EntrySet g_pGroundHogEntrySet;
inline EntrySet* GroundHogEntrySet() {return &g_pGroundHogEntrySet;};

#define GroundHogEntry(name, offset, returnType, pDetour, ...) \
    returnType pDetour(__VA_ARGS__); \
    typedef returnType (*pDetour##_t)(...); \
    ::Entry name(GroundHogEntrySet(), offset, pDetour); \
    returnType pDetour(__VA_ARGS__)


#endif //ALPHA_RING_GROUNDHOG_H
