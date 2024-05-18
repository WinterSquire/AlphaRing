#pragma once


struct player_info_t {

};

// size: 0x148
struct player_init_t {
    bool v_true;
    char un0[0x7];
    int user_input; // 0x8
    int input_map; // 0xC
    int respawn_flag; // 0x10
    int respawn_flag2; // 0x14
    char un2[0x8];
    wchar_t name[0x10]; // 0x20
    char un3[36];
    wchar_t id[0x4]; // 0x64
    char un4[180];
    wchar_t name2[0x10]; // 0x120
    char un5[0x8];
};