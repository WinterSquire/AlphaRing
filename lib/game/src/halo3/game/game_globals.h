#pragma once

#include "../base/base.h"

struct game_globals_definition {
    __int8 un[0x10];
    // size: 0xFB60
    struct map_info_t {
        __int8 game_type; // 1 campaign; 2 mp; 3 mainmenu
        __int8 un1[0x43];
        char name[0x104];
        char un0[0xA8];
        // size: 0xB8
        struct player_init_t {
            bool v_true;
            bool v_false;
            __int16 user_input;
            int input_map;
            int respawn_flag; // 0x8
            int unun;
            __int64 un_flag; // 0x10
            wchar_t name[0x10]; // 0x18
            char un1[0x1E];
            wchar_t id[0x3]; // 0x56
            char un2[0x34];
            wchar_t name2[0x10]; // 0x90
            char un3[0x8];
        } playerInit[16]; // 0x200
        __int8 un2[0xEE08];
        // 0xFB88 - 0xFB98
        __int8 skulls[0x10];
    } map_info;

    inline bool get_skull(eSkull skull) { return map_info.skulls[skull / 8] & (1 << (skull % 8)); }

    inline void set_skull(eSkull skull, bool enable) {
        if (enable) map_info.skulls[skull / 8] |= (1 << (skull % 8));
        else map_info.skulls[skull / 8] &= ~(1 << (skull % 8));
    }
};