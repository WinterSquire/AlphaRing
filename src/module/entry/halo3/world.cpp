#include "./halo3.h"

namespace Halo3::Entry::World {
    extern void Prologue(); extern void Epilogue();
    void detour();

    Halo3Entry(entry, OFFSET_HALO3_PF_WORLD, detour);
}

void Halo3::Entry::World::detour() {
    typedef void (__fastcall* func_t)();
    auto func = (func_t)entry.m_pOriginal;

    Prologue();
    func();
    Epilogue();
}