#include "halo4.h"

#include <functional>

namespace Halo4::Entry::World {void AddTask(const std::function<void()>& func);}

namespace Halo4::Entry::Render {
    void Prologue() {

    }

    void Epilogue() {
//        if (MainRenderer()->ShowContext() && MainRenderer()->NewFrame()) {
//            ImGui::Begin("Halo 4");
//            if (ImGui::Button("Add Player")) {
//                Halo4::Entry::World::AddTask([]() {
//                    NativeHalo4()->NativeFunc()->local_player_add(L"UWU", L"UWU");
//                });
//            }
//            ImGui::End();
//        }
    }

    Halo4Entry(entry, OFFSET_HALO4_PF_RENDER, void, detour) {
        Prologue();
        ((detour_t)entry.m_pOriginal)();
        Epilogue();
    }
}
