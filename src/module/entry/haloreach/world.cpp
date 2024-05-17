#include "./HaloReach.h"

namespace HaloReach::Entry::World {
    extern void Prologue(); extern void Epilogue();
    void detour();

    HaloReachEntry(entry, OFFSET_HALOREACH_PF_WORLD, detour);
}

void HaloReach::Entry::World::detour() {
    typedef void (__fastcall* func_t)();
    auto func = (func_t)entry.m_pOriginal;

    Prologue();
    func();
    Epilogue();
}