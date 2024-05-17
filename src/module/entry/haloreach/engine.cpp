#include "./haloreach.h"

namespace HaloReach::Entry::Engine {
    extern void Prologue(); extern void Epilogue();
    void detour();

    HaloReachEntry(entry, 0x34818, detour);
}

void HaloReach::Entry::Engine::detour() {
    typedef void (__fastcall* func_t)();
    auto func = (func_t)entry.m_pOriginal;

    Prologue();
    func();
    Epilogue();
}
