#include "../native.h"
#include "imgui.h"
#include "render/Renderer.h"

#include <functional>

namespace Halo4::Entry::Render { void Prologue(); void Epilogue(); }

void Halo4::Entry::Render::Prologue() {}

namespace Halo4::Entry::World {void AddTask(const std::function<void()>& func);}

void Halo4::Entry::Render::Epilogue() {
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
