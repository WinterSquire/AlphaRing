#include "imgui.h"
#include "hook/d3d11/imgui_impl.h"
#include "../imgui/page_halo3.h"

namespace Halo3::Entry::Render { void Prologue(); void Epilogue(); }

void Halo3::Entry::Render::Prologue() {}

void Halo3::Entry::Render::Epilogue() {
    ImmediateGUI::NewFrame();
    if (!ImmediateGUI::isVisible()) return;
    ImGui::Begin("Halo3");
    Halo3::IMGUI::page_halo3();
    ImGui::End();
}
