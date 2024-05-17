#include "Halo4.h"

namespace Halo4::Entry::Render {
    extern void Prologue(); extern void Epilogue();
    void detour();

    Halo4Entry(entry, OFFSET_HALO4_PF_RENDER, detour);
}

void Halo4::Entry::Render::detour() {
    typedef void (__fastcall* func_t)();
    auto func = (func_t)entry.m_pOriginal;

    Prologue();
    func();
    Epilogue();
}
