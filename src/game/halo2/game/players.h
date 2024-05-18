#pragma once


// size: 0xD4
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