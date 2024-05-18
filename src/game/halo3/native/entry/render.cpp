#include "../native.h"
#include "../../imgui/page_halo3.h"
#include "render/Renderer.h"

#include "imgui.h"

#include "halo3.h"

namespace Halo3::Entry::Render {
    void Prologue() {

    }

    void Epilogue() {
        static bool bShowContext = true;
        Halo3::IMGUI::update();

        bool bShow = Renderer()->ShowContext();

        if (bShowContext != bShow) {
            bShowContext = bShow;
            NativeHalo3()->Input()->enableInput(!bShowContext);
        }

        if (!bShowContext) return;

        Renderer()->NewFrame();
        ImGui::Begin("Halo3");
        Halo3::IMGUI::page_halo3();
        ImGui::End();
    }

    Halo3Entry(entry, OFFSET_HALO3_PF_RENDER, void, detour) {
        Prologue();
        ((detour_t)entry.m_pOriginal)();
        Epilogue();
    }
}
