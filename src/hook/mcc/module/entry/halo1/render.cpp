#include "halo1.h"
#include "hook/d3d11/main_renderer.h"

#include <Windows.h>

namespace Halo1::Entry::Render {
    void Prologue() {
        NativeHalo1()->NativeInfo()->update((__int64) GetModuleHandleA("halo1.dll"));
//
//        if (MainRenderer()->ShowContext() && MainRenderer()->NewFrame()) {
//            ImGui::Begin("Halo1");
//            auto p_player_count = (__int16*)(NativeHalo1()->NativeInfo()->getModuleAddress() + OFFSET_HALO1_PV_PLAYER_COUNT);
//
//            int player_count = *p_player_count;
//
//            if (ImGui::InputInt("Player Count", &player_count) && player_count >= 1 && player_count <= 4) {
//                *p_player_count = player_count;
//            }
//            ImGui::End();
//        }

    }

    void Epilogue() {

    }

    Halo1Entry(entry, OFFSET_HALO1_PF_RENDER, void, detour, void* a1, int a2) {
        Prologue();
        ((detour_t)entry.m_pOriginal)(a1, a2);
        Epilogue();
    }
}
