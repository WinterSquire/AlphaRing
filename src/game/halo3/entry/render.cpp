#include "../native_halo3.h"
#include "game/halo3/imgui/page_halo3.h"
#include "render/Renderer.h"

#include "imgui.h"

#include "halo3.h"

namespace Halo3::Entry::Render {
    void Prologue() {

    }

    void Epilogue() {
        Halo3::IMGUI::update();

        if (Renderer()->ShowContext() && Renderer()->NewFrame()) {
            ImGui::Begin("Halo3");
            Halo3::IMGUI::page_halo3();
            ImGui::End();
        }
    }

    Halo3Entry(entry, OFFSET_HALO3_PF_RENDER, void, detour) {
        Prologue();
        ((detour_t)entry.m_pOriginal)();
        Epilogue();
    }
}
