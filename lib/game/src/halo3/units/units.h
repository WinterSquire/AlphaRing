#pragma once

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