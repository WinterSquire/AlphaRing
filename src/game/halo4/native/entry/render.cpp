#include "../native.h"
#include "imgui.h"
#include "render/Renderer.h"

#include <functional>

#include "halo4.h"

namespace Halo4::Entry::World {void AddTask(const std::function<void()>& func);}

namespace Halo4::Entry::Render {
    void Prologue() {

    }

    void Epilogue() {
        static bool bShowContext = true;

        bool bShow = Renderer()->ShowContext();

        if (bShowContext != bShow) {
            bShowContext = bShow;
        }

        if (!bShowContext) return;

        Renderer()->NewFrame();
        ImGui::Begin("Halo 4");
        if (ImGui::Button("Add Player")) {
            Halo4::Entry::World::AddTask([]() {
                NativeHalo4()->NativeFunc()->local_player_add(L"UWU", L"UWU");
            });
        }
        ImGui::End();
    }

    Halo4Entry(entry, OFFSET_HALO4_PF_RENDER, void, detour) {
        Prologue();
        ((detour_t)entry.m_pOriginal)();
        Epilogue();
    }
}
