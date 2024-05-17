#include "haloreach.h"

namespace HaloReach::Entry::Render {
    extern void Prologue(); extern void Epilogue();
    void detour();

    HaloReachEntry(entry, 0xC3324, detour);
}

void HaloReach::Entry::Render::detour() {
    typedef void (__fastcall* func_t)();
    auto func = (func_t)entry.m_pOriginal;

    Prologue();
    func();
    Epilogue();
}
