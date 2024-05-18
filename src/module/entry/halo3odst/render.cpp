#include "Halo3ODST.h"

namespace Halo3ODST::Entry::Render {
    extern void Prologue(); extern void Epilogue();
    void detour();

    Halo3ODSTEntry(entry, OFFSET_HALO3ODST_PF_RENDER, detour);
}

void Halo3ODST::Entry::Render::detour() {
    typedef void (__fastcall* func_t)();
    auto func = (func_t)entry.m_pOriginal;

    Prologue();
    func();
    Epilogue();
}
