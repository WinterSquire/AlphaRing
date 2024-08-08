#pragma once

#include "./aim_assist.h"

struct player_action_definition {
    char control_context;
    char control_context_identifier;
    char un[6];
    __int64 control_flags;
    float yaw; // [0, 6.2831855]
    float pitch; // [-3.1415927, 3.1415927]
    float throttle_x; // [-1.0, 1.0]
    float throttle_y; // [-1.0, 1.0]
    bool map_editor_rotation_valid;
    bool map_editor_player_locked_for_manipulation;
    char padding[2];
    float map_editor_rotation_yaw; // [-1.0, 1.0]
    float map_editor_rotation_pitch; // [-1.0, 1.0]
    __int16 map_editor_flags;
    __int16 padding2;
    float trigger; // [0, 1.0]
    float secondary_trigger; // [0, 1.0]
    float raise_trigger; // [0, 1.0]
    float lower_trigger; // [0, 1.0]
    int action_flags;

    __int16 weapon_set_identifier;
    char primary_weapon_index;
    char secondary_weapon_index;
    __int16 grenade_index;
    __int16 zoom_level;
    __int16 interaction_type;
    __int16 interaction_data;
    INDEX interaction_object;
    INDEX melee_target_unit;

    aim_assist_definition aim_assist;

    char velocity_exceeds_motion_tracker_threshold;
    char padding3[3];
    __int64 action_test_flags;

    inline const char* get_interaction_name() {
        if (interaction_type == 1) return "interaction-pickup-flags";
        else if (interaction_type <= 5 || interaction_type == 8) return "interaction-seat-index";
        else return "interaction-unknown";
    }

    inline bool melee_target_exits() {return melee_target_unit != NONE;}
};

static_assert(sizeof(player_action_definition) == 136);

struct player_prediction_definition {
    int un0;
    int un1;
    char un2;
    char padding[3];
    Vector3 v1;
    Vector3 v2;
    Vector3 v3;
    Vector3 v4;
    Vector3 v5;
};

static_assert(sizeof(player_prediction_definition) == 72);