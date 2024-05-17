#include "haloreach.h"

namespace HaloReach::Entry::Render {
    extern void Prologue(); extern void Epilogue();
    void detour();

    HaloReachEntry(entry, OFFSET_HALOREACH_PF_RENDER, detour);
}

void HaloReach::Entry::Render::detour() {
    typedef void (__fastcall* func_t)();
    auto func = (func_t)entry.m_pOriginal;

    Prologue();
    func();
    Epilogue();
}
