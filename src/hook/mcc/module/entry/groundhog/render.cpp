#include "groundhog.h"

#include <functional>

namespace GroundHog::Entry::World {void AddTask(const std::function<void()>& func);}

namespace GroundHog::Entry::Render {
    void Prologue() {

    }

    void Epilogue() {
//        static bool bShowContext = true;
//
//        bool bShow = MainRenderer()->ShowContext();
//
//        if (bShowContext != bShow) {
//            bShowContext = bShow;
//        }
//
//        if (!bShowContext) return;
//
//        MainRenderer()->ShowContext() && MainRenderer()->NewFrame();
//        ImGui::Begin("GroundHog");
//        if (ImGui::Button("Add Player")) {
//            GroundHog::Entry::World::AddTask([]() {
//                NativeGroundHog()->NativeFunc()->local_player_add(L"UWU", L"UWU");
//            });
//        }
//        ImGui::End();
    }

    GroundHogEntry(entry, OFFSET_GROUNDHOG_PF_RENDER, void, detour) {
        Prologue();
        ((detour_t)entry.m_pOriginal)();
        Epilogue();
    }
}
