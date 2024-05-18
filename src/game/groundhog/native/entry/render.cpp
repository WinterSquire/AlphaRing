#include "../native.h"
#include "imgui.h"
#include "render/Renderer.h"

#include <functional>

namespace GroundHog::Entry::Render { void Prologue(); void Epilogue(); }

void GroundHog::Entry::Render::Prologue() {}

namespace GroundHog::Entry::World {void AddTask(const std::function<void()>& func);}

void GroundHog::Entry::Render::Epilogue() {
    static bool bShowContext = true;

    bool bShow = Renderer()->ShowContext();

    if (bShowContext != bShow) {
        bShowContext = bShow;
    }

    if (!bShowContext) return;

    Renderer()->NewFrame();
    ImGui::Begin("GroundHog");
    if (ImGui::Button("Add Player")) {
        GroundHog::Entry::World::AddTask([]() {
           NativeGroundHog()->NativeFunc()->local_player_add(L"UWU", L"UWU");
        });
    }
    ImGui::End();
}
