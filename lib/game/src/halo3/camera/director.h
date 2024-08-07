#pragma once

#include "../base/base.h"

struct director_globals_definition {
    struct cam_t {
        void *pp_func1;
        void *pp_mode_func;
        INDEX target;
        __int8 un0[0xC];
        Vector3 position;
        Radian3 rotation;
        __int8 un[0x120];
        int index; // 0x158
        __int8 un1[0x180 - 0x15C];
    } camera[MAX_LOCAL_PLAYERS];

    static_assert((sizeof(cam_t) == 0x180));

    __int8 un0[0x604 - MAX_LOCAL_PLAYERS * sizeof(cam_t)];

    // 0x604
    struct mode_t {
        int un_mode;
        eCameraMode mode;
        int un1;
    } mode[MAX_LOCAL_PLAYERS];
};