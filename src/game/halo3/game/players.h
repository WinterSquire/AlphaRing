#ifndef ALPHA_RING_PLAYERS_H
#define ALPHA_RING_PLAYERS_H

#include "../base/base.h"
#include "eTeam.h"

struct player_info_t;
struct player_action_t;

class ICPlayers {
public:
    virtual player_action_t* getPlayerAction() = 0;
    virtual entity_manager_t<player_info_t>* getPlayerManager() = 0;

};

extern ICPlayers* g_pICPlayers;
inline ICPlayers* Players() {return g_pICPlayers;};

struct player_action_t {
    __int32 un;
    bool disable_input;
};

struct player_info_t {
    __int8 v0[0x28];
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
