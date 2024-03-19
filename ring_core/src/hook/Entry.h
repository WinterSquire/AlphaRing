#ifndef ALPHA_RING_ENTRY_H
#define ALPHA_RING_ENTRY_H

#include "Common.h"

class Entry {
    using EntryFunction_t = void(*)();
    using ASMInitialize_t = void(__fastcall*)(void*, void*);
    using ASMHookEntry_t = void(__fastcall*)();

    Entry(__int64 offset, EntryFunction_t func, ASMInitialize_t init, ASMHookEntry_t entry);
    void Init();
    bool Check();
    
private:
    static bool bStatus;
    static bool bInit;
    static __int64 hModule;
    static vector<Entry*> s_entries;

    __int64 m_offset;
    __int64 m_pTarget;
    __int64 m_ppOriginal;
    EntryFunction_t m_scriptEntryFunc;

    ASMInitialize_t m_asmInitFunc;
    ASMHookEntry_t m_asmHookEntryFunc;
};


#endif //ALPHA_RING_ENTRY_H
