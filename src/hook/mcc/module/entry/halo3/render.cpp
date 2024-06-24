#include "halo3.h"

#include "hook/d3d11/main_renderer.h"

namespace Halo3::Entry::Render {
    void Prologue() {

    }

    void Epilogue() {
//        Halo3::IMGUI::update();

        MainRenderer()->Render(CMainRenderer::Halo3);
    }

    Halo3Entry(entry, OFFSET_HALO3_PF_RENDER, void, detour) {
        Prologue();
        ((detour_t)entry.m_pOriginal)();
        Epilogue();
    }
}
