#include "GroundHog.h"

namespace GroundHog::Entry::Render {
    extern void Prologue(); extern void Epilogue();
    void detour();

    GroundHogEntry(entry, OFFSET_GROUNDHOG_PF_RENDER, detour);
}

void GroundHog::Entry::Render::detour() {
    typedef void (__fastcall* func_t)();
    auto func = (func_t)entry.m_pOriginal;

    Prologue();
    func();
    Epilogue();
}
