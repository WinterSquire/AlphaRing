#include "halo3.h"

#include "render/Render.h"

namespace Halo3::Entry::Render {
    void Prologue() {

    }

    void Epilogue() {
        AlphaRing::Render::Render(AlphaRing::Render::Halo3);
    }

    Halo3Entry(entry, OFFSET_HALO3_PF_RENDER, void, detour) {
        Prologue();
        ((detour_t)entry.m_pOriginal)();
        Epilogue();
    }
}
