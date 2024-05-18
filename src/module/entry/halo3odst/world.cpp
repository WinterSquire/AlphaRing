#include "./Halo3ODST.h"

namespace Halo3ODST::Entry::World {
    extern void Prologue(); extern void Epilogue();
    void detour();

    Halo3ODSTEntry(entry, OFFSET_HALO3ODST_PF_WORLD, detour);
}

void Halo3ODST::Entry::World::detour() {
    typedef void (__fastcall* func_t)();
    auto func = (func_t)entry.m_pOriginal;

    Prologue();
    func();
    Epilogue();
}