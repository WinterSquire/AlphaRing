#pragma once

#include "../base/base.h"

struct aim_assist_definition {
    INDEX target_player;
    INDEX target_object;
    INDEX model_target;
    float primary_autoaim_level; // [0, 1]
    float secondary_autoaim_level; // [0, 1]
    Vector3 lead_vector;
    char flags;
    char buffer[3];

    inline bool autoaim_exits() {return (flags & 2) != 0 || target_object != NONE;}
};