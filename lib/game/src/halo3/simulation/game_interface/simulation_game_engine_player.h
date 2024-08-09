#pragma once

#include "../../base/base.h"

#include "../../game/game_engine_player_traits.h"

struct game_engine_player_state {
    int waypoint_action;
    float respawn_timer1;
    Vector3 dead_location;
    c_player_traits player_traits;
    bool blocking_teleporter;
    char un;
    __int16 lives_remaining;
    int last_betrayer;
    __int16 respawn_timer2;
    bool vehicle_entrance_ban;
    bool active_in_game;
    bool sitting_out_exists;
    char un1;
    __int16 desired_respawn_player;
    Vector3 player_control_aiming;
};