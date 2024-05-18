#include "./Halo2.h"

namespace Halo2::Entry::World {
    extern void Prologue(); extern void Epilogue();
    void detour();

    Halo2Entry(entry, OFFSET_HALO2_PF_WORLD, detour);
}

void Halo2::Entry::World::detour() {
    typedef void (__fastcall* func_t)();
    auto func = (func_t)entry.m_pOriginal;

    Prologue();
    func();
    Epilogue();
}