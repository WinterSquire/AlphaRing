#ifndef ALPHA_RING_HALO2_H
#define ALPHA_RING_HALO2_H


#include "offset_Halo2.h"

#include "../entry.h"


extern EntrySet g_pHalo2EntrySet;
inline EntrySet* Halo2EntrySet() {return &g_pHalo2EntrySet;};

#define Halo2Entry(name, offset, pDetour) ::Entry name(Halo2EntrySet(), offset, pDetour)


#endif //ALPHA_RING_HALO2_H
