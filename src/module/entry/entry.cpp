#include "entry.h"

#include <cassert>

#include "MinHook.h"

Entry::Entry(EntrySet* set, __int64 offset, void *pDetour) {
    m_pOriginal = nullptr;
    m_pDetour = pDetour;
    m_offset = offset;
    m_target = 0;

    set->append(this);
}

bool Entry::update(__int64 hModule) {
    MH_STATUS status;

    if (hModule == 0) return false;

    if (m_target) MH_RemoveHook((void*)m_target, true);

    m_target = m_offset + hModule;

    status = MH_CreateHook((void*)m_target, (void*)m_pDetour, (void**)&m_pOriginal);

    if (status != MH_OK) return false;

    status = MH_EnableHook((void*)m_target);

    if (status != MH_OK) return false;

    return true;
}

void EntrySet::append(Entry *entry) {
    assert(entryCount < MAX_ENTRY);
    entryArray[entryCount++] = entry;
}

bool EntrySet::update(__int64 hModule) {
    bool result = true;

    if (hModule == 0) return false;

    for (int i = 0; i < entryCount; ++i) result &= entryArray[i]->update(hModule);

    return result;
}
