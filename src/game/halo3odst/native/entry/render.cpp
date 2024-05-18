#include "../native.h"
#include "imgui.h"
#include "render/Renderer.h"

#include <functional>

namespace Halo3ODST::Entry::Render { void Prologue(); void Epilogue(); }

void Halo3ODST::Entry::Render::Prologue() {}

namespace Halo3ODST::Entry::World {void AddTask(const std::function<void()>& func);}

void Halo3ODST::Entry::Render::Epilogue() {
    static bool bShowContext = true;

    bool bShow = Renderer()->ShowContext();

    if (bShowContext != bShow) {
        bShowContext = bShow;
    }

    if (!bShowContext) return;

    Renderer()->NewFrame();
    ImGui::Begin("Halo3 ODST");
    if (ImGui::Button("Add Player")) {
        Halo3ODST::Entry::World::AddTask([]() {
           NativeHalo3ODST()->NativeFunc()->local_player_add(L"UWU", L"UWU");
        });
    }
    ImGui::End();
}
