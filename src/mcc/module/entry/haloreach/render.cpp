#include "haloreach.h"

#include <functional>

namespace HaloReach::Entry::World {void AddTask(const std::function<void()>& func);}

namespace HaloReach::Entry::Render {
    void Prologue() {

    }
    void Epilogue() {
//        if (MainRenderer()->ShowContext() && MainRenderer()->NewFrame()) {
//            ImGui::Begin("Halo Reach");
//            if (ImGui::Button("Add Player")) {
//                HaloReach::Entry::World::AddTask([]() {
//                    NativeHaloReach()->NativeFunc()->local_player_add(L"UWU", L"UWU");
//                });
//            }
//            ImGui::End();
//        }
    }
    HaloReachEntry(entry, OFFSET_HALOREACH_PF_RENDER, void, detour) {
        Prologue();
        ((detour_t)entry.m_pOriginal)();
        Epilogue();
    }
}
