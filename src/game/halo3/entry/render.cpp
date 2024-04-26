#include "imgui.h"
#include "hook/d3d11/imgui_impl.h"
#include "../imgui/page_halo3.h"
#include "../input/input.h"

namespace Halo3::Entry::Render { void Prologue(); void Epilogue(); }

void Halo3::Entry::Render::Prologue() {}

void Halo3::Entry::Render::Epilogue() {
    Halo3::IMGUI::update();

    if (!ImmediateGUI::isVisible()) {
        Input()->enableInput(true);
        return;
    } else {
        Input()->enableInput(false);
    }

    ImmediateGUI::NewFrame();
    ImGui::Begin("Halo3");
    Halo3::IMGUI::page_halo3();
    ImGui::End();
}
