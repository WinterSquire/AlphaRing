#include "imgui.h"
#include "render/Renderer.h"
#include "../imgui/page_halo3.h"
#include "../native/native.h"

namespace Halo3::Entry::Render { void Prologue(); void Epilogue(); }

void Halo3::Entry::Render::Prologue() {}

void Halo3::Entry::Render::Epilogue() {
    static bool bShowContext = true;
    Halo3::IMGUI::update();

    if (Renderer()->ShowContext() != bShowContext) {
        bShowContext = Renderer()->ShowContext();
        if (bShowContext) {
            NativeHalo3()->Input()->enableInput(false);
        } else {
            NativeHalo3()->Input()->enableInput(true);
        }
    }

    if (!bShowContext) return;

    Renderer()->NewFrame();
    ImGui::Begin("NativeHalo3");
    Halo3::IMGUI::page_halo3();
    ImGui::End();
}
