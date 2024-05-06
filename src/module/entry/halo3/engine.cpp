#include "./halo3.h"

namespace Halo3::Entry::Engine {
    extern void Prologue(); extern void Epilogue();
    void detour();

    Halo3Entry(entry, OFFSET_HALO3_PF_ENGINE, detour);
}

void Halo3::Entry::Engine::detour() {
    typedef void (__fastcall* func_t)();
    auto func = (func_t)entry.m_pOriginal;

    Prologue();
    func();
    Epilogue();
}
