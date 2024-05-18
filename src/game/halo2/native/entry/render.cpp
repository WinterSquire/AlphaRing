#include "../native.h"
#include "imgui.h"
#include "render/Renderer.h"

#include <functional>

namespace Halo2::Entry::Render { void Prologue(); void Epilogue(); }

void Halo2::Entry::Render::Prologue() {

}

namespace Halo2::Entry::World {void AddTask(const std::function<void()>& func);}

void Halo2::Entry::Render::Epilogue() {
    static bool bShowContext = true;

    bool bShow = Renderer()->ShowContext();

    if (bShowContext != bShow) {
        bShowContext = bShow;
    }

    if (!bShowContext) return;

    Renderer()->NewFrame();
    ImGui::Begin("Halo 2");
    if (ImGui::Button("Add Player")) {
        Halo2::Entry::World::AddTask([]() {
           NativeHalo2()->NativeFunc()->local_player_add(L"UWU", L"UWU");
        });
    }
    ImGui::End();
}
