#include "entry.h"

#include <cassert>

#include "MinHook.h"

const int MAX_ENTRY = 20;

static int entryCount = 0;
static Entry* entryArray[MAX_ENTRY];

Entry::Entry(__int64 offset, __int64 pDetour) : m_offset(offset), m_pDetour(pDetour), m_target(0) {
    assert(entryCount < MAX_ENTRY);
    entryArray[entryCount++] = this;
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

bool Entry::update_all(__int64 hModule) {
    bool result = true;

    if (hModule == 0) return false;

    for (int i = 0; i < entryCount; ++i) result &= entryArray[i]->update(hModule);

    return result;
}
