#pragma once

#include "../game/aim_assist.h"
#include "../objects/objects.h"

struct units_definition : objects_definition {
    enum eUnitFlags {
        _biped_setting_relaxation_pose_bit = 0x200,
    };

    __int8 v9[0x54];
    INDEX actor_index;//0x168
    __int8 v10[0x4];
    __int32 unit_flags;
    eTeamAI team; //0x174
    t_Player player_index; //0x178
    __int8 v11[0xA0]; //0x20C?
    INDEX aim_target; //0x21C
    __int8 v12[0x14C];
    float camo_time;
    __int64 un;
    float crouch_progress; // [0, 1.0]
    __int8 v13[0xE4];
    __int16 biped_flags;
    __int8 v14[0x42];
    INDEX bump_target; // 1188
    __int8 bump_close;

    // 0x460 __int16 biped.flags

    inline bool FlashLight(){return unit_flags & 0x8000000u;}
    inline void FlashLight(bool b){if(b) unit_flags |= 0x8000000u;else damage_flags &= ~0x8000000u;}
    inline bool CanMove(){return unit_flags & 0x3u;}
    inline void CanMove(bool b){if(b) unit_flags |= 0x3u;else unit_flags &= ~0x3u;}
    inline void EnableCamo() { unit_flags |= 0x10u | 0x8u; }
    inline void SetCamo(float time) { EnableCamo(); camo_time = time; }
};

struct unit_control_definition {
    const static int k_maximum_weapons_per_unit = 4;
    const static int k_unit_grenade_types_count = 4;
    const static __int16 k_unit_aiming_speeds_count = 0x8000;

    int identifier;
    __int16 un;
    __int16 weapon_set_identifier;
    char primary_weapon_indices;
    char secondary_weapon_indices;
    __int16 grenade_index;
    __int16 zoom_level;
    __int16 interaction_type;
    __int64 action_flags;
    Vector3 throttle; // 24 movement
    float primary_trigger;
    float secondary_trigger;
    Vector3 facing_vector;
    Vector3 aiming_vector;
    Vector3 looking_vector;
    Vector3 gaze_position;
    aim_assist_definition aim_assist_data;
};