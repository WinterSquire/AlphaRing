#include "../native.h"
#include "imgui.h"
#include "render/Renderer.h"

#include <functional>

namespace HaloReach::Entry::Render { void Prologue(); void Epilogue(); }

void HaloReach::Entry::Render::Prologue() {}

namespace HaloReach::Entry::World {void AddTask(const std::function<void()>& func);}

void HaloReach::Entry::Render::Epilogue() {
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
