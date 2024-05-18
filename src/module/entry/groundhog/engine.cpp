#include "./GroundHog.h"

namespace GroundHog::Entry::Engine {
    extern void Prologue(); extern void Epilogue();
    void detour();

    GroundHogEntry(entry, OFFSET_GROUNDHOG_PF_ENGINE, detour);
}

void GroundHog::Entry::Engine::detour() {
    typedef void (__fastcall* func_t)();
    auto func = (func_t)entry.m_pOriginal;

    Prologue();
    func();
    Epilogue();
}
