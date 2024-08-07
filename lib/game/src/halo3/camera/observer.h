#pragma once

#include "../base/base.h"

struct observer_globals_definition {
    struct raw_data_t {
        __int8 un0[0x11C];
        struct data_t {
            Vector3 position;
            float un;
            Vector3 velocity;
            Vector3 v_rotation;
            Vector3 components;
        } data;
        __int8 un1[0x280];
    } data[MAX_LOCAL_PLAYERS];
    static_assert(sizeof(raw_data_t) == 0x3D0);
};