#pragma once

#include "base.h"
#include "game/ICNative.h"

#include "offset_haloreach.h"

DefNative(HaloReach) {
    namespace Function {
        // Main Thread
        // Don't use these functions directly in Render Thread!
        INDEX player_add(const wchar_t *name, const wchar_t *id, bool isClient);
    }

    DefEntryEntity(Players, OFFSET_HALOREACH_V_ENTRY_PLAYERS) {

    };

    struct split_screen_t {
        int un0;
        INDEX map_player[4]; // 0x4
        char un1[0x20];
        INDEX input_player[4]; // 0x34
        char un2[0x30];
        int index[4];// 0x74
        int un3[3 * 4];// 0x84
        int screen_count; // 0xB4
        INDEX player_INDEX[4]; // 0xB8
        INDEX object_INDEX[4]; // 0xC8
        __int8 players[4]; // 0xD8
    };
}
