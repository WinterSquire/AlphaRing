#include "./GroundHog.h"

namespace GroundHog::Entry::World {
    extern void Prologue(); extern void Epilogue();
    void detour();

    GroundHogEntry(entry, OFFSET_GROUNDHOG_PF_WORLD, detour);
}

void GroundHog::Entry::World::detour() {
    typedef void (__fastcall* func_t)();
    auto func = (func_t)entry.m_pOriginal;

    Prologue();
    func();
    Epilogue();
}