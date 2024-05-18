#ifndef ALPHA_RING_GROUNDHOG_H
#define ALPHA_RING_GROUNDHOG_H


#include "offset_groundhog.h"

#include "../entry.h"


extern EntrySet g_pGroundHogEntrySet;
inline EntrySet* GroundHogEntrySet() {return &g_pGroundHogEntrySet;};

#define GroundHogEntry(name, offset, pDetour) ::Entry name(GroundHogEntrySet(), offset, pDetour)


#endif //ALPHA_RING_GROUNDHOG_H
