#ifndef ALPHA_RING_PLAYERS_H
#define ALPHA_RING_PLAYERS_H

#include "../base/base.h"
#include "eTeam.h"

#include "../../ICNative.h"

struct player_info_t;
struct player_action_t;
struct player_init_t;

class ICPlayers {
public:
    virtual player_action_t* getPlayerAction() = 0;
    virtual entity_manager_t<player_info_t>* getPlayerManager() = 0;
};

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
};

struct player_action_t {
    __int32 player_count;
    bool disable_input;
};

struct player_info_t {
    int Index; // 0x0000EC71
    char flags_0; // (1 << 3) black screen
    char flags_1;
    __int8 v0[0x22];
    INDEX object_INDEX; // 0x28 can't modify directly
    INDEX restore_INDEX; // 0x2C
    __int8 v1[0x1C];
    Vector3 position;// 0x4C
    wchar_t name[0x10]; // 0x58
    bool pref_voice;//0x78
    __int8 primary_color;
    __int8 secondary_color;
    __int8 tertiary_color;
    bool pref_species; // 0x7C
    __int8 v3[0x19];
    wchar_t id[4]; // 0x96
    __int8 v4[0x50];
    unsigned int team; // 0xF0
    __int8 v5[0xAC];
    unsigned int respawn_time; // 0x1A0
    __int8 v6[0x33];// 0x1AC respawn_time_second
    __int8 coop_index;// 0x1D7
    __int8 v7[0x2];
    __int8 v8[0x22];// 0xBC
    __int8 player_shield;
    __int8 v9[0x3];
    __int8 v10[0xC];
    __int8 player_camo;
    __int8 v11[0x87];
    Vector3 position2;// 0x294
    INDEX object_INDEX2;
    INDEX restore_INDEX2;
    float uk0,uk1,uk2;
    __int8 v20[0x3C];
};

#endif //ALPHA_RING_PLAYERS_H
