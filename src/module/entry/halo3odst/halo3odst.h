#ifndef ALPHA_RING_HALO3ODST_H
#define ALPHA_RING_HALO3ODST_H


#include "offset_halo3odst.h"

#include "../entry.h"


extern EntrySet g_pHalo3ODSTEntrySet;
inline EntrySet* Halo3ODSTEntrySet() {return &g_pHalo3ODSTEntrySet;};

#define Halo3ODSTEntry(name, offset, pDetour) ::Entry name(Halo3ODSTEntrySet(), offset, pDetour)


#endif //ALPHA_RING_HALO3ODST_H
