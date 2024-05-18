#pragma once


struct player_info_t {

};

// size: 0x98
struct player_init_t {
    bool v_true;
    bool v_false;
    __int16 user_input;
    int input_map;
    int respawn_flag; // 0x8
    int unun;
    __int64 un_flag; // 0x10
    wchar_t name[0x10]; // 0x18
    char un1[22];
    wchar_t id[0x3]; // 0x4E
    char un2[28];
    wchar_t name2[0x10]; // 0x70
    char un3[0x8];
};