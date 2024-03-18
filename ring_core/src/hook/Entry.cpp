#include "Entry.h"

#include "MinHook.h"

bool Entry::bInit = false;
bool Entry::bStatus = false;
__int64 Entry::hModule = 0;

void Entry::Init() {

}

void Entry::Regist(Entry::EntryFunction_t func) {

}

bool Entry::Check() {
    m_pTarget = hModule + m_offset;
    if (*(BYTE*)m_pTarget == 0xE9) return true;
    MH_DisableHook((LPVOID)m_pTarget);
    MH_CreateHook((LPVOID)m_pTarget, m_asmHookEntryFunc, (LPVOID *) &m_ppOriginal);
    MH_EnableHook((LPVOID)m_pTarget);
    return false;
}
