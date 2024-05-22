#include "../native.h"

#include "imgui.h"

#include "halo2.h"

#include <windows.h>

namespace Halo2::Entry::Load {bool IsLoading();}

namespace Halo2::Entry::Player {
    struct player_init_t {
        bool v_true;
        bool un0;
        __int16 user_input; // 0x2
        int input_map; // 0x4
        __int64 respawn_flag; // 0x8
        char un2[0x8];
        wchar_t name[0x10]; // 0x18
        char un3[48];
        wchar_t id[0x4]; // 0x68
        char un4[0x64];
    };

    void Prologue() {
        auto hModule = (__int64)GetModuleHandleA("halo2.dll");
        auto p_players = (player_init_t*)(*(__int64*)(hModule + 0xE7FA78) + 0xAC4);

        for (int i = 1; i < 4; i++) {
            auto p_player = p_players + i;
            p_player->v_true = true;
            p_player->user_input = p_player->input_map = i;
            p_player->respawn_flag = *(__int64*)(*(__int64*)(hModule + OFFSET_HALO2_PV_RESPAWN) + 0x30);
        }
    }

    Halo2Entry(entry, 0x6A5D90, __int64, detour) {
        Prologue();
        return ((detour_t)entry.m_pOriginal)();
    }
}
