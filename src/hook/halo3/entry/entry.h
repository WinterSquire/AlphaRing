#ifndef ALPHA_RING_ENTRY_H
#define ALPHA_RING_ENTRY_H

class Entry {
public:
    using func_t = void(*)();

    Entry(__int64 offset, __int64 pDetour);

    bool update(__int64 hModule);
    inline func_t getPointerOriginal() const { return (Entry::func_t)m_pOriginal; }
    inline static __int64 gethModule() { return m_hModule; }

    static bool update_all(__int64 hModule);

private:
    static __int64 m_hModule;

    const __int64 m_offset;
    __int64 m_target;
    __int64 m_pDetour;
    __int64 m_pOriginal;

};


#endif //ALPHA_RING_ENTRY_H
