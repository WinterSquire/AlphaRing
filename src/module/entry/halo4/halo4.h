#ifndef ALPHA_RING_HALO4_H
#define ALPHA_RING_HALO4_H


#include "offset_halo4.h"

#include "../entry.h"


extern EntrySet g_pHalo4EntrySet;
inline EntrySet* Halo4EntrySet() {return &g_pHalo4EntrySet;};

#define Halo4Entry(name, offset, pDetour) ::Entry name(Halo4EntrySet(), offset, pDetour)


#endif //ALPHA_RING_HALO4_H
