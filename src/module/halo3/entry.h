#ifndef ALPHA_RING_ENTRY_H
#define ALPHA_RING_ENTRY_H

#include "offset_halo3.h"

class Entry {
public:
    Entry(__int64 offset, void *pDetour);

    bool update(__int64 hModule);
    inline void* pOriginal() const { return m_pOriginal; }

    static bool update_all(__int64 hModule);

private:
    const __int64 m_offset;
    __int64 m_target;
    void* m_pDetour;
    void* m_pOriginal;

};


#endif //ALPHA_RING_ENTRY_H
