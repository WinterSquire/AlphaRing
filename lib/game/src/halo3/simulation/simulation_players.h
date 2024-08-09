#pragma once

#include "simulation.h"
#include "../networking/network_game_definitions.h"

#pragma pack(push, 1)

struct c_player_update {
    INDEX player_index;
    __int64 player_identifier;
    int update_type;
    machine_identifier_definition machine_identifier;
    INDEX user_index;
    INDEX controller_index;
    bool player_left_game;
    bool player_joined_in_progress;
    __int64 un;
    c_player_configuration configuration;
    int swap_player_index;
    char swap_player_identifier[12];
};

static_assert(sizeof(c_player_update) == 216);

#pragma pack(pop)