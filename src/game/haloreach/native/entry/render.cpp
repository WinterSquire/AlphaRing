#include "../native.h"
#include "imgui.h"
#include "render/Renderer.h"

#include <functional>

#include "haloreach.h"

namespace HaloReach::Entry::World {void AddTask(const std::function<void()>& func);}

namespace HaloReach::Entry::Render {
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
        ImGui::Begin("Halo Reach");
        if (ImGui::Button("Add Player")) {
            HaloReach::Entry::World::AddTask([]() {
                NativeHaloReach()->NativeFunc()->local_player_add(L"UWU", L"UWU");
            });
        }
        ImGui::End();
    }
    HaloReachEntry(entry, OFFSET_HALOREACH_PF_RENDER, void, detour) {
        Prologue();
        ((detour_t)entry.m_pOriginal)();
        Epilogue();
    }
}
