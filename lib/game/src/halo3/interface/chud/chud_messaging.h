#pragma once

#include "../../base/base.h"

struct chud_persistent_user_data1_definition {
    struct player_chud_t {
        char un0[0x6c];
        bool chud_texture_cam; // offset: 0x6C
        char un1;
        bool cinematic_scripting_destroy_cortana_effect_cinematic; // offset: 0x6E
        char un2[0x1F8C - 0x6F];
        // offset: 0x1F8Ci64 size: ?
        struct msg_t {
            // offset: 0x90 size: 0xE8i64
            struct str_t {
                wchar_t text[0x60]; // 0x0
                int un0 = 0x100; // 0xC0
                int game_time = 0x100; // 0xC4
                int un1; // 0xC8
                int un2 = 0; // 0xCC
                int un4[5]; // 0xD0
                int un3 = 2; // 0xE4
            } str[6];

            static_assert((sizeof(str_t) == 0xE8));
        } msg;
        char un3[0x28C8 - (0x1F8C + sizeof(msg_t))];
    } player[MAX_LOCAL_PLAYERS];

    static_assert((sizeof(player_chud_t) == 0x28C8));
};