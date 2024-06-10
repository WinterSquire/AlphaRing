#include "game/halo4/native.h"
#include "imgui/imgui.h"
#include "render/Renderer.h"

#include <functional>

#include "halo4.h"

namespace Halo4::Entry::World {void AddTask(const std::function<void()>& func);}

namespace Halo4::Entry::Render {
    void Prologue() {

    }

    void Epilogue() {
        if (Renderer()->ShowContext() && Renderer()->NewFrame()) {
            ImGui::Begin("Halo 4");
            if (ImGui::Button("Add Player")) {
                Halo4::Entry::World::AddTask([]() {
                    Halo4::Native::Function::local_player_add(L"UWU", L"UWU");
                });
            }
            ImGui::End();
        }
    }

    Halo4Entry(entry, OFFSET_HALO4_PF_RENDER, void, detour) {
        Prologue();
        ((detour_t)entry.m_pOriginal)();
        Epilogue();
    }
}
