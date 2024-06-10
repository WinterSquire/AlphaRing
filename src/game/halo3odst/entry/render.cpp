#include "game/halo3odst/native.h"
#include "imgui/imgui.h"
#include "render/Renderer.h"
#include <functional>

#include "halo3odst.h"

namespace Halo3ODST::Entry::World {void AddTask(const std::function<void()>& func);}

namespace Halo3ODST::Entry::Render {
    void Prologue() {

    }

    void Epilogue() {
        if (Renderer()->ShowContext() && Renderer()->NewFrame()) {
            ImGui::Begin("Halo3 ODST");
            if (ImGui::Button("Add Player")) {
                Halo3ODST::Entry::World::AddTask([]() {
                    Halo3ODST::Native::Function::local_player_add(L"UWU", L"UWU");
                });
            }
            ImGui::End();
        }
    }

    Halo3ODSTEntry(entry, OFFSET_HALO3ODST_PF_RENDER, void, detour) {
        Prologue();
        ((detour_t)entry.m_pOriginal)();
        Epilogue();
    }
}
