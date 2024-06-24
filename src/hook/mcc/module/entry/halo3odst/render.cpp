#include "halo3odst.h"

#include <functional>

namespace Halo3ODST::Entry::World {void AddTask(const std::function<void()>& func);}

namespace Halo3ODST::Entry::Render {
    void Prologue() {

    }

    void Epilogue() {
//        if (MainRenderer()->ShowContext() && MainRenderer()->NewFrame()) {
//            ImGui::Begin("Halo3 ODST");
//            if (ImGui::Button("Add Player")) {
//                Halo3ODST::Entry::World::AddTask([]() {
//                    NativeHalo3ODST()->NativeFunc()->local_player_add(L"UWU", L"UWU");
//                });
//            }
//            ImGui::End();
//        }
    }

    Halo3ODSTEntry(entry, OFFSET_HALO3ODST_PF_RENDER, void, detour) {
        Prologue();
        ((detour_t)entry.m_pOriginal)();
        Epilogue();
    }
}
