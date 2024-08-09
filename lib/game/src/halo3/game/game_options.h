#pragma once

struct c_game_player_options {
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
};

static_assert(sizeof(c_game_player_options) == 184);