#pragma once

#include "../base/base.h"

#include "../networking/network_game_definitions.h"
#include "../simulation/game_interface/simulation_game_engine_player.h"
#include "../simulation/simulation.h"

struct players_globals_definition {
    __int32 player_count;
    bool disable_input;
};

#pragma pack(push, 1)

struct players_definition {
    int Index;
    int flags;
    __int64 player_identifier; // xuid
    int unnn;
    machine_identifier_definition machine_identifier;
    __int16 machine_index;
    __int16 machine_user_index;
    __int16 controller_index;
    __int16 machine_controller_index;
    __int16 machine_controller_index1;
    char cluster_reference;
    char padding[3];
    Datum unit_datum; // 40
    INDEX restore_INDEX; // 0x2C
    __int8 v1[0x1C];
    Vector3 position;// 0x4C
    c_player_configuration configuration; // 88
    __int8 v5[0xA8];
    unsigned int respawn_time; // 0x1A0
    __int8 v6[0x33];// 0x1AC respawn_time_second
    __int8 coop_index;// 0x1D7
    __int8 v7[0x2];
    __int8 v8[30];
    c_player_traits traits;
    struct Multiplayer {
        float powerup_pickup_time[4];
    };
    __int8 v11[128];
    Vector3 position2;// 0x294
    INDEX object_INDEX2;
    INDEX restore_INDEX2;
    float uk0, uk1, uk2;
    __int8 v20[0x3C];
};

static_assert((sizeof(players_definition) == 0x2F0));

#pragma pack(pop)