#include "../native.h"

#include "imgui/imgui.h"

#include "halo2.h"
#include "render/Renderer.h"

namespace Halo2::Entry::Load {bool IsLoading();}

namespace Halo2::Entry::Game {
    void Prologue() {
        if (!Load::IsLoading() && Renderer()->ShowContext() && Renderer()->NewFrame()) {
            ImGui::Begin("Halo 2");
            if (ImGui::Button("Add Player")) {
                NativeHalo2()->NativeFunc()->local_player_add(L"UWU", L"UWU");
            }
            ImGui::End();
        }
    }

    void Epilogue() {

    }

    Halo2Entry(entry, OFFSET_HALO2_PF_GAME, void, detour) {
        Prologue();
        ((detour_t)entry.m_pOriginal)();
        Epilogue();
    }
}
