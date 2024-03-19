#include "Entry.h"

#include "MinHook.h"

bool Entry::bInit = false;
bool Entry::bStatus = false;
__int64 Entry::hModule = 0;
vector<Entry*> Entry::s_entries;

Entry::Entry(__int64 offset, Entry::EntryFunction_t func, Entry::ASMInitialize_t init, Entry::ASMHookEntry_t entry)
    : m_offset(offset), m_scriptEntryFunc(func), m_asmInitFunc(init), m_asmHookEntryFunc(entry) {
    s_entries.push_back(this);
}

void Entry::Init() {
    m_asmInitFunc(m_scriptEntryFunc, &m_ppOriginal);
}

bool Entry::Check() {
    m_pTarget = hModule + m_offset;
    if (*(BYTE*)m_pTarget == 0xE9) return true;
    MH_DisableHook((LPVOID)m_pTarget);
    MH_CreateHook((LPVOID)m_pTarget, m_asmHookEntryFunc, (LPVOID *) &m_ppOriginal);
    MH_EnableHook((LPVOID)m_pTarget);
    return false;
}
