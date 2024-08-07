#pragma once

#include "../base/base.h"

struct physics_constants_definition {
    float gravity;
    float v0;
    float v1;
    float v2;
    float un;
    float v3;
    float v4;
    float v5;

    inline static const float GRAVITY = 4.1712594f;

    inline void reset() {
        gravity = GRAVITY;
        v0 = 1.0f;
        v1 = 0.0011f;           // 0x3A902DE0
        v2 = 0;
        un = 0;
        v3 = 0;
        v4 = 0;
        v5 = cosf(0.61086524);
    }

    inline void set_gravity(float scale) { gravity = scale * GRAVITY; }
};