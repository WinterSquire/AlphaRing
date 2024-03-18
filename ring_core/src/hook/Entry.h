#ifndef ALPHA_RING_ENTRY_H
#define ALPHA_RING_ENTRY_H


class Entry {
    using EntryFunction_t = void(*)();
    using ASMInitialize_t = void(__fastcall*)(void*, void*);
    using ASMHookEntry_t = void(__fastcall*)();

    void Init();
    void Regist(EntryFunction_t func);
    bool Check();
    
private:
    static bool bStatus;
    static bool bInit;
    static __int64 hModule;

    __int64 m_offset;
    __int64 m_pTarget;
    __int64 m_ppOriginal;
    EntryFunction_t m_scriptEntryFunc;

    ASMInitialize_t m_asmInitFunc;
    ASMHookEntry_t m_asmHookEntryFunc;
};


#endif //ALPHA_RING_ENTRY_H
